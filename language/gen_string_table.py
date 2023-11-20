# -*- coding: utf-8 -*-

#1.0.0
#WPR
#20210715

import sys
import math
import os
import re
import time
from datetime import datetime
import openpyxl

def add_bom(file):
    bom_mask = b'\xEF\xBB\xBF'
    with open(file, 'r+b') as f:
        org_contents = f.read()
        f.seek(0)
        f.write(bom_mask + org_contents)
        f.close()
        
        
def main(argv):
    gCurrDir = os.getcwd()
    gLanguageTypeArray = []
    dataColMax = 0
    dataRowIndex = 0
    title = "//"
    c_file = gCurrDir + "/" + "language_table.c"
    h_file = gCurrDir + "/" + "language_table.h"

    if os.path.exists(c_file) == True:
        os.remove(c_file)
    if os.path.exists(h_file) == True:
        os.remove(h_file)


    writeFileHand_c = open(c_file, "w", encoding="utf-8")
    writeFileHand_h = open(h_file, "w", encoding="utf-8")

    writeFileHand_h.write("#ifndef __LANGUAGE_IDS_H__\n")
    writeFileHand_h.write("#define __LANGUAGE_IDS_H__\n\n")
    writeFileHand_h.write("typedef enum{\n")
    writeFileHand_h.write("\tSTRING_NULL = 0,\n")

    writeFileHand_c.write("#include \"language.h\"\n\n")
    writeFileHand_c.write("const language_strings_struct language_strings[] =\n")
    writeFileHand_c.write("{\n")

    gExcelFilePath = gCurrDir + "/" + "language.xlsx"
    gExcelFileData = openpyxl.load_workbook(gExcelFilePath,data_only=True)
    gSheetData = gExcelFileData['language']
    
    for dataRow in gSheetData.rows:
        dataRowIndex = dataRowIndex + 1

        #第一行 注释语言名称
        if(dataRowIndex == 1):
            #查找总列数
            for dataIndex in range(1,len(dataRow)):
                if(dataRow[dataIndex].value == None):
                    break
                dataColMax = dataIndex + 1
                
            #生成标题
            for dataIndex in range(1,dataColMax):
                title += str(dataRow[dataIndex].value)
                if(dataIndex < dataColMax-1):
                    title += ",  "
            writeFileHand_c.write('\t'+title+'\n')
            print(title)
            continue

        #第二行 生成 gLanguageTypeArray
        if(dataRowIndex == 2):
            for dataIndex in range(1,dataColMax):
                gLanguageTypeArray.append("LANGUAGE_TYPE_"+str(dataRow[dataIndex].value))
            continue

        #第二次扫描到行首单元格为空，退出
        if(dataRow[0].value == 0):
            break

        writeFileHand_h.write('\t' + str(dataRow[0].value) + ',\n')
        
        content = "{" + str(dataRow[0].value) + ",  "
        for dataIndex in range(1,dataColMax):
            if(dataRow[dataIndex].value == None):
                content +='"'+'"' 
            else:
                str_val = str(dataRow[dataIndex].value)
                content +='"' + str_val.replace('"', "'") +'"' 
                
            if(dataIndex < dataColMax-1):
                content += ",  "
                
        content += "},"
        writeFileHand_c.write('\t'+content+'\n')
        #print(content)

    writeFileHand_c.write("};\n\n")
    
    writeFileHand_c.write("const unsigned char sys_language_type[] = {\n")
    writeFileHand_c.write("\t" + title + '\n')
    for langItem in gLanguageTypeArray:
        writeFileHand_c.write('\t' + langItem + ',\n')
    writeFileHand_c.write("};\n\n")


    writeFileHand_c.write("unsigned int sys_language_get_strings_number(void)\n")
    writeFileHand_c.write("{\n")
    writeFileHand_c.write("\treturn (sizeof(language_strings) / sizeof(language_strings[0]));\n")
    writeFileHand_c.write("}\n\n")

    writeFileHand_c.write("unsigned int sys_language_get_number(void)\n")
    writeFileHand_c.write("{\n")
    writeFileHand_c.write("\treturn (sizeof(sys_language_type) / sizeof(sys_language_type[0]));\n")
    writeFileHand_c.write("}\n\n")
    writeFileHand_c.close()

    writeFileHand_h.write("\tSTRING_MAX_ID,\n")
    writeFileHand_h.write("}STRING_ID_TYPE;\n\n")
    writeFileHand_h.write("#endif\n")
    writeFileHand_h.close()

    # 添加BOM标志字节, Keil环境不支持utf8.
    add_bom(gCurrDir + "/" + "language_table.c")
    add_bom(gCurrDir + "/" + "language_table.h")



if __name__ == "__main__":
    main(sys.argv)
