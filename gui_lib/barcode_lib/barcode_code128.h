#ifndef __BARCODE_CODE128_H__
#define __BARCODE_CODE128_H__

#include "feature_all.h"

#define C128_MAX 160

#define C128_LATCHA 'A'
#define C128_LATCHB 'B'
#define C128_LATCHC 'C'
#define C128_SHIFTA 'a'
#define C128_SHIFTB 'b'
#define C128_ABORC '9'
#define C128_AORB 'Z'

/* Warning and error conditions (API return values) */
#define ZINT_WARN_INVALID_OPTION 2    /* Invalid option given but overridden by Zint */
#define ZINT_WARN_USES_ECI 3          /* Automatic ECI inserted by Zint */
#define ZINT_WARN_NONCOMPLIANT 4      /* Symbol created not compliant with standards */
#define ZINT_ERROR 5                  /* Warn/error marker, not returned */
#define ZINT_ERROR_TOO_LONG 5         /* Input data wrong length */
#define ZINT_ERROR_INVALID_DATA 6     /* Input data incorrect */
#define ZINT_ERROR_INVALID_CHECK 7    /* Input check digit incorrect */
#define ZINT_ERROR_INVALID_OPTION 8   /* Incorrect option given */
#define ZINT_ERROR_ENCODING_PROBLEM 9 /* Internal error (should not happen) */
#define ZINT_ERROR_FILE_ACCESS 10     /* Error opening output file */
#define ZINT_ERROR_MEMORY 11          /* Memory allocation (malloc) failure */
#define ZINT_ERROR_FILE_WRITE 12      /* Error writing to output file */
#define ZINT_ERROR_USES_ECI 13        /* Error counterpart of warning if WARN_FAIL_ALL set (see below) */
#define ZINT_ERROR_NONCOMPLIANT 14    /* Error counterpart of warning if WARN_FAIL_ALL set */

/* Output options (`symbol->output_options`) */
#define BARCODE_BIND_TOP 0x0001        /* Boundary bar above the symbol only (not below), does not affect stacking */
                                       /* Note: value was once used by the legacy (never-used) BARCODE_NO_ASCII */
#define BARCODE_BIND 0x0002            /* Boundary bars above & below the symbol and between stacked symbols */
#define BARCODE_BOX 0x0004             /* Box around symbol */
#define BARCODE_STDOUT 0x0008          /* Output to stdout */
#define READER_INIT 0x0010             /* Reader Initialisation (Programming) */
#define SMALL_TEXT 0x0020              /* Use smaller font */
#define BOLD_TEXT 0x0040               /* Use bold font */
#define CMYK_COLOUR 0x0080             /* CMYK colour space (Encapsulated PostScript and TIF) */
#define BARCODE_DOTTY_MODE 0x0100      /* Plot a matrix symbol using dots rather than squares */
#define GS1_GS_SEPARATOR 0x0200        /* Use GS instead of FNC1 as GS1 separator (Data Matrix) */
#define OUT_BUFFER_INTERMEDIATE 0x0400 /* Return ASCII values in bitmap buffer (OUT_BUFFER only) */
#define BARCODE_QUIET_ZONES 0x0800     /* Add compliant quiet zones (additional to any specified whitespace) */
                                       /* Note: CODE16K, CODE49, CODABLOCKF, ITF14, EAN/UPC have default quiet zones
                                        */
#define BARCODE_NO_QUIET_ZONES 0x1000  /* Disable quiet zones, notably those with defaults as listed above */
#define COMPLIANT_HEIGHT 0x2000        /* Warn if height not compliant and use standard height (if any) as default */

/* Input data types (`symbol->input_mode`) */
#define DATA_MODE 0    /* Binary */
#define UNICODE_MODE 1 /* UTF-8 */
#define GS1_MODE 2     /* GS1 */
/* The following may be OR-ed with above */
#define ESCAPE_MODE 0x0008       /* Process escape sequences */
#define GS1PARENS_MODE 0x0010    /* Process parentheses as GS1 AI delimiters (instead of square brackets) */
#define GS1NOCHECK_MODE 0x0020   /* Do not check validity of GS1 data (except that printable ASCII only) */
#define HEIGHTPERROW_MODE 0x0040 /* Interpret `height` as per-row rather than as overall height */
#define FAST_MODE 0x0080         /* Use faster if less optimal encodation or other shortcuts if available */
                                 /* Note: affects DATAMATRIX, MICROPDF417, PDF417, QRCODE & UPNQR only */
#define EXTRA_ESCAPE_MODE 0x0100 /* Process special symbology-specific escape sequences */
                                 /* Note: currently Code 128 only */

/* Symbologies (`symbol->symbology`) */
/* Tbarcode 7 codes */
#define BARCODE_CODABAR 18   /* Codabar */
#define BARCODE_CODE128 20   /* Code 128 */
#define BARCODE_CODE16K 23   /* Code 16k */
#define BARCODE_CODE49 24    /* Code 49 */
#define BARCODE_CODE93 25    /* Code 93 */
#define BARCODE_QRCODE 58    /* QR Code */
#define BARCODE_CODE128AB 60 /* Code 128 (Suppress Code Set C) */
#define BARCODE_CODE128B 60  /* Legacy */

#define BARCODE_MAX_INPUT_DATA_LEN (60)
#define BARCODE_CODE128C_OTHER_LEN (3)
#define BARCODE_CODE128C_START_CHAR (105)
#define BARCODE_CODE128C_STOP_CHAR (106)
#define BARCODE_CODE128C_MAX_CHAR (7)

/* Main symbol structure */
typedef struct _zint_symbol
{
    short symbology;             /* Symbol to use (see BARCODE_XXX below) */
    short output_options;        /* Various output parameters (bind, box etc, see below) */
    short input_mode;            /* Encoding of input data (see DATA_MODE etc below). Default DATA_MODE */
    short width;                 /* Width of the generated symbol (output only) */
    unsigned char *encoded_data; /*Encoded data (output only).*/
    unsigned char encoded_data_count;
} zint_symbol;

extern int barcode_code128_create(zint_symbol *symbol, unsigned char *source, int length);
extern const unsigned char *barcode_code128_get_line(unsigned char index);

extern unsigned int barcode_code128_get_width(unsigned char* code_string);
#endif