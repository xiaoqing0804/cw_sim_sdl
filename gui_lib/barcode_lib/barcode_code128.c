/* code128.c - Handles Code 128 and derivatives */
/*
	libzint - the open source barcode library
	Copyright (C) 2008-2023 Robin Stuart <rstuart114@gmail.com>
	Bugfixes thanks to Christian Sakowski and BogDan Vatra

	Redistribution and use in source and binary forms, with or without
	modification, are permitted provided that the following conditions
	are met:

	1. Redistributions of source code must retain the above copyright
	   notice, this list of conditions and the following disclaimer.
	2. Redistributions in binary form must reproduce the above copyright
	   notice, this list of conditions and the following disclaimer in the
	   documentation and/or other materials provided with the distribution.
	3. Neither the name of the project nor the names of its contributors
	   may be used to endorse or promote products derived from this software
	   without specific prior written permission.

	THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
	ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
	IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
	ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE
	FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
	DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
	OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
	HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
	LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
	OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
	SUCH DAMAGE.
 */
/* SPDX-License-Identifier: BSD-3-Clause */

#include <stdio.h>
#include "os_mem.h"
#include "barcode_code128.h"
#include "system_util_string.h"

static const unsigned char *C128Table[107] = {
	"212222", "222122", "222221", "121223",
	"121322", "131222", "122213", "122312",
	"132212", "221213", "221312", "231212",
	"112232", "122132", "122231", "113222",
	"123122", "123221", "223211", "221132",
	"221231", "213212", "223112", "312131",
	"311222", "321122", "321221", "312212",
	"322112", "322211", "212123", "212321",
	"232121", "111323", "131123", "131321",
	"112313", "132113", "132311", "211313",
	"231113", "231311", "112133", "112331",
	"132131", "113123", "113321", "133121",
	"313121", "211331", "231131", "213113",
	"213311", "213131", "311123", "311321",
	"331121", "312113", "312311", "332111",
	"314111", "221411", "431111", "111224",
	"111422", "121124", "121421", "141122",
	"141221", "112214", "112412", "122114",
	"122411", "142112", "142211", "241211",
	"221114", "413111", "241112", "134111",
	"111242", "121142", "121241", "114212",
	"124112", "124211", "411212", "421112",
	"421211", "212141", "214121", "412121",
	"111143", "111341", "131141", "114113",
	"114311", "411113", "411311", "113141",
	"114131", "311141", "411131", "211412",
	"211214", "211232", "2331112"};

/* Determine appropriate mode for a given character */
static int c128_parunmodd(const unsigned char llyth)
{
	int modd;

	if (llyth <= 31)
	{
		modd = C128_SHIFTA;
	}
	else if ((llyth >= 48) && (llyth <= 57))
	{
		modd = C128_ABORC;
	}
	else if (llyth <= 95)
	{
		modd = C128_AORB;
	}
	else if (llyth <= 127)
	{
		modd = C128_SHIFTB;
	}
	else if (llyth <= 159)
	{
		modd = C128_SHIFTA;
	}
	else if (llyth <= 223)
	{
		modd = C128_AORB;
	}
	else
	{
		modd = C128_SHIFTB;
	}

	return modd;
}

/**
 * Bring together same type blocks
 */
static void c128_grwp(int list[2][C128_MAX], int *p_indexliste)
{
	/* bring together same type blocks */
	if (*p_indexliste > 1)
	{
		int i = 1;
		while (i < *p_indexliste)
		{
			if (list[1][i - 1] == list[1][i])
			{
				int j;
				/* bring together */
				list[0][i - 1] = list[0][i - 1] + list[0][i];
				j = i + 1;

				/* decrease the list */
				while (j < *p_indexliste)
				{
					list[0][j - 1] = list[0][j];
					list[1][j - 1] = list[1][j];
					j++;
				}
				*p_indexliste = *p_indexliste - 1;
				i--;
			}
			i++;
		}
	}
}

/**
 * Implements rules from ISO 15417 Annex E
 */
static void c128_dxsmooth(int list[2][C128_MAX], int *p_indexliste, const char *manual_set)
{
	int i, last, next;
	const int indexliste = *p_indexliste;

	for (i = 0; i < indexliste; i++)
	{
		int current = list[1][i]; /* Either C128_ABORC, C128_AORB, C128_SHIFTA or C128_SHIFTB */
		int length = list[0][i];
		if (i != 0)
		{
			last = list[1][i - 1];
		}
		else
		{
			last = 0;
		}
		if (i != indexliste - 1)
		{
			next = list[1][i + 1];
		}
		else
		{
			next = 0;
		}

		if (i == 0)
		{ /* first block */
			if (current == C128_ABORC)
			{
				if (manual_set && manual_set[i])
				{
					list[1][i] = manual_set[i];
					current = manual_set[i];
				}
				else if ((indexliste == 1) && (length == 2))
				{
					/* Rule 1a */
					list[1][i] = C128_LATCHC;
					current = C128_LATCHC;
				}
				else if (length >= 4)
				{
					/* Rule 1b */
					list[1][i] = C128_LATCHC;
					current = C128_LATCHC;
				}
				else
				{
					current = C128_AORB; /* Determine below */
				}
			}
			if (current == C128_AORB)
			{
				if (manual_set && (manual_set[i] == 'A' || manual_set[i] == 'B'))
				{
					list[1][i] = manual_set[i];
				}
				else if (next == C128_SHIFTA)
				{
					/* Rule 1c */
					list[1][i] = C128_LATCHA;
				}
				else
				{
					/* Rule 1d */
					list[1][i] = C128_LATCHB;
				}
			}
			else if (current == C128_SHIFTA)
			{
				/* Rule 1c */
				list[1][i] = C128_LATCHA;
			}
			else if (current == C128_SHIFTB)
			{ /* Unless C128_LATCHX set above, can only be C128_SHIFTB */
				/* Rule 1d */
				list[1][i] = C128_LATCHB;
			}
		}
		else
		{
			if (current == C128_ABORC)
			{
				if (manual_set && manual_set[i])
				{
					list[1][i] = manual_set[i];
					current = manual_set[i];
				}
				else if (length >= 4)
				{
					/* Rule 3 - note Rule 3b (odd C blocks) dealt with later */
					list[1][i] = C128_LATCHC;
					current = C128_LATCHC;
				}
				else
				{
					current = C128_AORB; /* Determine below */
				}
			}
			if (current == C128_AORB)
			{
				if (manual_set && (manual_set[i] == 'A' || manual_set[i] == 'B'))
				{
					list[1][i] = manual_set[i];
				}
				else if (last == C128_LATCHA || last == C128_SHIFTB)
				{ /* Maintain state */
					list[1][i] = C128_LATCHA;
				}
				else if (last == C128_LATCHB || last == C128_SHIFTA)
				{ /* Maintain state */
					list[1][i] = C128_LATCHB;
				}
				else if (next == C128_SHIFTA)
				{
					list[1][i] = C128_LATCHA;
				}
				else
				{
					list[1][i] = C128_LATCHB;
				}
			}
			else if (current == C128_SHIFTA)
			{
				if (manual_set && manual_set[i] == 'A')
				{
					list[1][i] = C128_LATCHA;
				}
				else if (length > 1)
				{
					/* Rule 4 */
					list[1][i] = C128_LATCHA;
				}
				else if (last == C128_LATCHA || last == C128_SHIFTB)
				{ /* Maintain state */
					list[1][i] = C128_LATCHA;
				}
				else if (last == C128_LATCHC)
				{
					list[1][i] = C128_LATCHA;
				}
			}
			else if (current == C128_SHIFTB)
			{ /* Unless C128_LATCHX set above, can only be C128_SHIFTB */
				if (manual_set && manual_set[i] == 'B')
				{
					list[1][i] = C128_LATCHB;
				}
				else if (length > 1)
				{
					/* Rule 5 */
					list[1][i] = C128_LATCHB;
				}
				else if (last == C128_LATCHB || last == C128_SHIFTA)
				{ /* Maintain state */
					list[1][i] = C128_LATCHB;
				}
				else if (last == C128_LATCHC)
				{
					list[1][i] = C128_LATCHB;
				}
			}
		} /* Rule 2 is implemented elsewhere, Rule 6 is implied */
	}

	c128_grwp(list, p_indexliste);
}

/**
 * Translate Code 128 Set A characters into barcodes.
 * This set handles all control characters NUL to US.
 */
static void c128_set_a(const unsigned char source, int values[], int *bar_chars)
{
	if (source > 127)
	{
		if (source < 160)
		{
			values[(*bar_chars)] = (source - 128) + 64;
		}
		else
		{
			values[(*bar_chars)] = (source - 128) - 32;
		}
	}
	else
	{
		if (source < 32)
		{
			values[(*bar_chars)] = source + 64;
		}
		else
		{
			values[(*bar_chars)] = source - 32;
		}
	}
	(*bar_chars)++;
}

/**
 * Translate Code 128 Set B characters into barcodes.
 * This set handles all characters which are not part of long numbers and not
 * control characters.
 */
static int c128_set_b(const unsigned char source, int values[], int *bar_chars)
{
	if (source >= 128 + 32)
	{
		values[(*bar_chars)] = source - 32 - 128;
	}
	else if (source >= 128)
	{			  /* Should never happen */
		return 0; /* Not reached */
	}
	else if (source >= 32)
	{
		values[(*bar_chars)] = source - 32;
	}
	else
	{			  /* Should never happen */
		return 0; /* Not reached */
	}
	(*bar_chars)++;
	return 1;
}

/* Translate Code 128 Set C characters into barcodes
 * This set handles numbers in a compressed form
 */
static void c128_set_c(const unsigned char source_a, const unsigned char source_b, int values[], int *bar_chars)
{
	int weight;

	weight = (10 * ctoi(source_a)) + ctoi(source_b);
	values[(*bar_chars)] = weight;
	(*bar_chars)++;
}

/* Put set data into set[]. If source given (GS1_MODE) then resolves odd C blocks */
void c128_put_in_set(int list[2][C128_MAX], const int indexliste, char set[C128_MAX],
					 const unsigned char *source)
{
	int read = 0;
	int i, j;

	for (i = 0; i < indexliste; i++)
	{
		for (j = 0; j < list[0][i]; j++)
		{
			set[read++] = list[1][i];
		}
	}
	if (source)
	{
		/* Watch out for odd-length Mode C blocks */
		int c_count = 0;
		for (i = 0; i < read; i++)
		{
			if (set[i] == 'C')
			{
				if (source[i] == '[')
				{
					if (c_count & 1)
					{
						if ((i - c_count) != 0)
						{
							set[i - c_count] = 'B';
						}
						else
						{
							set[i - 1] = 'B';
						}
					}
					c_count = 0;
				}
				else
				{
					c_count++;
				}
			}
			else
			{
				if (c_count & 1)
				{
					if ((i - c_count) != 0)
					{
						set[i - c_count] = 'B';
					}
					else
					{
						set[i - 1] = 'B';
					}
				}
				c_count = 0;
			}
		}
		if (c_count & 1)
		{
			if ((i - c_count) != 0)
			{
				set[i - c_count] = 'B';
			}
			else
			{
				set[i - 1] = 'B';
			}
		}
		for (i = 1; i < read - 1; i++)
		{
			if ((set[i] == 'C') && ((set[i - 1] == 'B') && (set[i + 1] == 'B')))
			{
				set[i] = 'B';
			}
		}
	}
}

/* Handle Code 128, 128B and HIBC 128 */
int barcode_code128_create_code(zint_symbol *symbol, unsigned char *source, int length, int list[2][C128_MAX])
{
	if (length > C128_MAX)
	{
		/* This only blocks ridiculously long input - the actual length of the
		   resulting barcode depends on the type of data, so this is trapped later */
		return ZINT_ERROR_TOO_LONG;
	}

	int i, j, k, bar_characters = 0, read, total_sum;
	int error_number = 0, indexchaine, indexliste, f_state = 0;
	unsigned char *src = source;

	char mode, last_set, current_set = ' ';
	int glyph_count = 0; /* Codeword estimate times 2 */
	unsigned char *d = symbol->encoded_data;

	// int values[C128_MAX] = {0};
	int *values = os_mem_alloc(RAM_TYPE_BUFFER_ON, C128_MAX * 4);
	memset(values, 0, C128_MAX * 4);

	// unsigned char src_buf[C128_MAX + 1];
	unsigned char *src_buf = os_mem_alloc(RAM_TYPE_BUFFER_ON, C128_MAX + 1);

	// char manual_set[C128_MAX] = {0};
	char *manual_set = os_mem_alloc(RAM_TYPE_BUFFER_ON, C128_MAX);
	memset(manual_set, 0, C128_MAX);

	// char set[C128_MAX] = {0};
	char *set = os_mem_alloc(RAM_TYPE_BUFFER_ON, C128_MAX);
	memset(set, 0, C128_MAX);

	// char fset[C128_MAX] = {0};
	char *fset = os_mem_alloc(RAM_TYPE_BUFFER_ON, C128_MAX);
	memset(fset, 0, C128_MAX);

	/* Detect special Code Set escapes for Code 128 in extra escape mode only */
	if ((symbol->input_mode & EXTRA_ESCAPE_MODE) && symbol->symbology == BARCODE_CODE128)
	{
		char manual_ch = '\0';
		j = 0;
		for (i = 0; i < length; i++)
		{
			if (source[i] == '\\' && i + 2 < length && source[i + 1] == '^' && ((source[i + 2] >= 'A' && source[i + 2] <= 'C') || source[i + 2] == '^'))
			{
				if (source[i + 2] != '^')
				{
					i += 2;
					manual_ch = source[i];
				}
				else
				{ /* Escape sequence '\^^' */
					manual_set[j] = manual_ch;
					src_buf[j++] = source[i++];
					manual_set[j] = manual_ch;
					src_buf[j++] = source[i++];
					/* Drop second '^' */
				}
			}
			else
			{
				manual_set[j] = manual_ch;
				src_buf[j++] = source[i];
			}
		}
		if (j != length)
		{
			length = j;
			if (length == 0)
			{
				os_mem_free((void *)values);
				os_mem_free((void *)src_buf);
				os_mem_free((void *)manual_set);
				os_mem_free((void *)set);
				os_mem_free((void *)fset);
				return ZINT_ERROR_INVALID_DATA;
			}
			src = src_buf;
			src[length] = '\0';
		}
	}

	/* Detect extended ASCII characters */
	for (i = 0; i < length; i++)
	{
		fset[i] = src[i] >= 128 ? 'f' : ' ';
	}

	/* Decide when to latch to extended mode - Annex E note 3 */
	j = 0;
	for (i = 0; i < length; i++)
	{
		if (fset[i] == 'f')
		{
			j++;
		}
		else
		{
			j = 0;
		}

		if (j >= 5)
		{
			for (k = i; k > (i - 5); k--)
			{
				fset[k] = 'F';
			}
		}

		if ((j >= 3) && (i == (length - 1)))
		{
			for (k = i; k > (i - 3); k--)
			{
				fset[k] = 'F';
			}
		}
	}

	/* Decide if it is worth reverting to 646 encodation for a few characters as described in 4.3.4.2 (d) */
	for (i = 1; i < length; i++)
	{
		if ((fset[i - 1] == 'F') && (fset[i] == ' '))
		{
			/* Detected a change from 8859-1 to 646 - count how long for */
			for (j = 0; ((i + j) < length) && (fset[i + j] == ' '); j++)
				;
			/* Count how many 8859-1 beyond */
			k = 0;
			if (i + j < length)
			{
				for (k = 1; ((i + j + k) < length) && (fset[i + j + k] != ' '); k++)
					;
			}
			if (j < 3 || (j < 5 && k > 2))
			{
				/* Change to shifting back rather than latching back */
				/* Inverts the same figures recommended by Annex E note 3 */
				for (k = 0; k < j; k++)
				{
					fset[i + k] = 'n';
				}
			}
		}
	}

	/* Decide on mode using same system as PDF417 and rules of ISO 15417 Annex E */
	indexliste = 0;
	indexchaine = 0;

	mode = c128_parunmodd(src[indexchaine]);
	if (mode == C128_ABORC && (symbol->symbology == BARCODE_CODE128AB || (manual_set[indexchaine] == 'A' || manual_set[indexchaine] == 'B')))
	{
		mode = C128_AORB;
	}

	do
	{
		list[1][indexliste] = mode;
		while ((list[1][indexliste] == mode) && (indexchaine < length))
		{
			list[0][indexliste]++;
			indexchaine++;
			if (indexchaine == length)
			{
				break;
			}
			mode = c128_parunmodd(src[indexchaine]);
			if (mode == C128_ABORC && (symbol->symbology == BARCODE_CODE128AB || (manual_set[indexchaine] == 'A' || manual_set[indexchaine] == 'B')))
			{
				mode = C128_AORB;
			}
			if (manual_set[indexchaine] != manual_set[indexchaine - 1])
			{
				break;
			}
		}
		indexliste++;
	} while (indexchaine < length);

	if (src == src_buf)
	{
		/* Need to re-index `manual_set` to have sames indexes as `list` blocks for `c128_dxsmooth()` */
		j = 0;
		for (i = 1; i < indexliste; i++)
		{
			j += list[0][i - 1];
			manual_set[i] = manual_set[j];
		}
	}
	c128_dxsmooth(list, &indexliste, src == src_buf ? manual_set : NULL);

	/* Resolve odd length C128_LATCHC blocks */
	if ((list[1][0] == C128_LATCHC) && (list[0][0] & 1))
	{
		/* Rule 2 */
		list[0][1]++;
		list[0][0]--;
		if (indexliste == 1)
		{
			list[0][1] = 1;
			list[1][1] = C128_LATCHB;
			indexliste = 2;
		}
	}
	if (indexliste > 1)
	{
		for (i = 1; i < indexliste; i++)
		{
			if ((list[1][i] == C128_LATCHC) && (list[0][i] & 1))
			{
				/* Rule 3b */
				list[0][i - 1]++;
				list[0][i]--;
			}
		}
	}

	/* Put set data into set[]. Giving NULL as source as used to resolve odd C blocks which has been done above */
	c128_put_in_set(list, indexliste, set, NULL /*source*/);

	/* Now we can calculate how long the barcode is going to be - and stop it from being too long */
	last_set = set[0];
	for (i = 0; i < length; i++)
	{
		if ((set[i] == 'a') || (set[i] == 'b'))
		{
			glyph_count += 2; /* 1 codeword */
		}
		if ((fset[i] == 'f') || (fset[i] == 'n'))
		{
			glyph_count += 2; /* May be overestimate if in latch */
		}
		if (((set[i] == 'A') || (set[i] == 'B')) || (set[i] == 'C'))
		{
			if (set[i] != last_set)
			{
				last_set = set[i];
				glyph_count += 2;
			}
		}
		if (i == 0)
		{
			if (fset[i] == 'F')
			{
				glyph_count += 4; /* 2 codewords */
			}
		}
		else
		{
			if ((fset[i] == 'F') && (fset[i - 1] != 'F'))
			{
				glyph_count += 4;
			}
			if ((fset[i] != 'F') && (fset[i - 1] == 'F'))
			{
				glyph_count += 4;
			}
		}

		if (set[i] == 'C')
		{
			glyph_count += 1; /* Half a codeword */
		}
		else
		{
			glyph_count += 2;
		}
	}
	if (glyph_count > 120) /* 60 * 2 */
	{
		os_mem_free((void *)values);
		os_mem_free((void *)src_buf);
		os_mem_free((void *)manual_set);
		os_mem_free((void *)set);
		os_mem_free((void *)fset);
		// strcpy(symbol->errtxt, "341: Input too long (60 symbol character maximum)");
		return ZINT_ERROR_TOO_LONG;
	}

	/* So now we know what start character to use - we can get on with it! */
	if (symbol->output_options & READER_INIT)
	{
		/* Reader Initialisation mode */
		switch (set[0])
		{
		case 'A': /* Start A */
			values[bar_characters++] = 103;
			current_set = 'A';
			values[bar_characters++] = 96; /* FNC3 */
			break;
		case 'B': /* Start B */
			values[bar_characters++] = 104;
			current_set = 'B';
			values[bar_characters++] = 96; /* FNC3 */
			break;
		case 'C':							/* Start C */
			values[bar_characters++] = 104; /* Start B */
			values[bar_characters++] = 96;	/* FNC3 */
			values[bar_characters++] = 99;	/* Code C */
			current_set = 'C';
			break;
		}
	}
	else
	{
		/* Normal mode */
		switch (set[0])
		{
		case 'A': /* Start A */
			values[bar_characters++] = 103;
			current_set = 'A';
			break;
		case 'B': /* Start B */
			values[bar_characters++] = 104;
			current_set = 'B';
			break;
		case 'C': /* Start C */
			values[bar_characters++] = 105;
			current_set = 'C';
			break;
		}
	}

	if (fset[0] == 'F')
	{
		switch (current_set)
		{
		case 'A':
			values[bar_characters++] = 101;
			values[bar_characters++] = 101;
			f_state = 1;
			break;
		case 'B':
			values[bar_characters++] = 100;
			values[bar_characters++] = 100;
			f_state = 1;
			break;
		}
	}

	/* Encode the data */
	read = 0;
	do
	{
		if ((read != 0) && (set[read] != current_set))
		{
			/* Latch different code set */
			switch (set[read])
			{
			case 'A':
				values[bar_characters++] = 101;
				current_set = 'A';
				break;
			case 'B':
				values[bar_characters++] = 100;
				current_set = 'B';
				break;
			case 'C':
				values[bar_characters++] = 99;
				current_set = 'C';
				break;
			}
		}

		if (read != 0)
		{
			if ((fset[read] == 'F') && (f_state == 0))
			{
				/* Latch beginning of extended mode */
				switch (current_set)
				{
				case 'A':
					values[bar_characters++] = 101;
					values[bar_characters++] = 101;
					f_state = 1;
					break;
				case 'B':
					values[bar_characters++] = 100;
					values[bar_characters++] = 100;
					f_state = 1;
					break;
				}
			}
			if ((fset[read] == ' ') && (f_state == 1))
			{
				/* Latch end of extended mode */
				switch (current_set)
				{
				case 'A':
					values[bar_characters++] = 101;
					values[bar_characters++] = 101;
					f_state = 0;
					break;
				case 'B':
					values[bar_characters++] = 100;
					values[bar_characters++] = 100;
					f_state = 0;
					break;
				}
			}
		}

		if ((fset[read] == 'f' && f_state == 0) || (fset[read] == 'n' && f_state == 1))
		{
			/* Shift to or from extended mode */
			switch (current_set)
			{
			case 'A':
				values[bar_characters++] = 101; /* FNC 4 */
				break;
			case 'B':
				values[bar_characters++] = 100; /* FNC 4 */
				break;
			}
		}

		if ((set[read] == 'a') || (set[read] == 'b'))
		{
			/* Insert shift character */
			values[bar_characters++] = 98;
		}

		switch (set[read]) /* Encode data characters */
		{
		case 'a':
		case 'A':
			c128_set_a(src[read], values, &bar_characters);
			read++;
			break;
		case 'b':
		case 'B':
			(void)c128_set_b(src[read], values, &bar_characters);
			read++;
			break;
		case 'C':
			c128_set_c(src[read], src[read + 1], values, &bar_characters);
			read += 2;
			break;
		}

	} while (read < length);

	symbol->width = 0;
	symbol->encoded_data_count = 0;

	/* Destination setting and check digit calculation */
	*d++ = values[0];
	symbol->encoded_data_count++;
	symbol->width += 11;

	total_sum = values[0];
	for (i = 1; i < bar_characters; i++)
	{
		*d++ = values[i];
		symbol->width += 11;
		symbol->encoded_data_count++;
		total_sum += values[i] * i; /* Note can't overflow as 106 * 60 * 60 = 381600 */
	}
	total_sum %= 103;
	*d++ = total_sum;
	symbol->width += 11;
	symbol->encoded_data_count++;
	values[bar_characters++] = total_sum;

	/* Stop character */
	*d++ = 106;
	symbol->width += 13;
	symbol->encoded_data_count++;
	values[bar_characters++] = 106;

#if 0
	SYS_DEBUG("code128 symbol->encoded_data_count = %d", symbol->encoded_data_count);
	SYS_DEBUG("code128 symbol->width = %d", symbol->width);
	for (short i = 0; i < symbol->encoded_data_count; i++)
	{
		SYS_DEBUG("code128  i = %d symbol->encoded_data = %d", i, symbol->encoded_data[i]);
	}
#endif

	os_mem_free((void *)values);
	os_mem_free((void *)src_buf);
	os_mem_free((void *)manual_set);
	os_mem_free((void *)set);
	os_mem_free((void *)fset);

	return error_number;
}

int barcode_code128_create(zint_symbol *symbol, unsigned char *source, int length)
{
	SYS_DEBUG("code128 source = %s", source);

	int *list = os_mem_alloc(RAM_TYPE_BUFFER_ON, 2 * C128_MAX * 4);
	memset(list, 0, 2 * C128_MAX * 4);
	int result = barcode_code128_create_code(symbol, source, length, list);
	os_mem_free((void *)list);
	return result;
}

const unsigned char *barcode_code128_get_line(unsigned char index)
{
	if (index >= countof(C128Table))
		index = 0;
	return C128Table[index];
}

// 计算条形码的宽度 ... 
unsigned int barcode_code128_get_width(unsigned char* code_string)
{
    unsigned int len = 0;
	zint_symbol *symbol = os_mem_alloc(RAM_TYPE_BUFFER_ON, sizeof(zint_symbol) + C128_MAX);
    if (symbol != NULL) {
        symbol->input_mode = DATA_MODE;
        symbol->symbology = BARCODE_CODE128;
        symbol->output_options = 0;
        symbol->encoded_data = (unsigned char*)(symbol + 1);
        barcode_code128_create(symbol, (unsigned char *)code_string, strlen(code_string));
        len = symbol->width;
        os_mem_free((void *)symbol);
    }
    return len;
}


