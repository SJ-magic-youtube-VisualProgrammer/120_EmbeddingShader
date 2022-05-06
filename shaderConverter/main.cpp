/************************************************************
■C++ 文字列/文字を置き換える(replace)
	https://itsakura.com/cpp-replace

■C++ 文字列の連結と追加【std::string｜文字列結合と挿入処理】
	https://marycore.jp/prog/cpp/concat-append-string/
************************************************************/
#include <stdio.h>
#include <string>
// #include <regex>

/************************************************************
************************************************************/

/******************************
******************************/
int main(int argc, char** argv){
	/********************
	********************/
	std::string str_FileName_src = "data/";
	std::string str_FileName_dst = "data/";
	
	for(int i = 1; i < argc; i++){
		if( strcmp(argv[i], "-i") == 0 ){
			if(i+1 < argc) { str_FileName_src += argv[i + 1]; }
		}else if( strcmp(argv[i], "-o") == 0 ){
			if(i+1 < argc) { str_FileName_dst += argv[i + 1]; }
		}
	}
	
	if( (str_FileName_src == "data/") || (str_FileName_dst == "data/") ){
		printf("> I'll show the input format below.\n");
		printf("\tShaderConverter -i inputFileName -o outputFileName\n");
		return -1;
	}
	
	/********************
	********************/
	FILE* fp_src = fopen(str_FileName_src.c_str(), "r");
	if( fp_src == NULL ) { printf("ERROR opening : %s\n", str_FileName_src.c_str()); return -1; }
	
	FILE* fp_dst = fopen(str_FileName_dst.c_str(), "w");
	if( fp_dst == NULL ) { fclose(fp_src); printf("ERROR opening : %s\n", str_FileName_dst.c_str()); return -1; }
	
	
	/********************
	********************/
	fprintf(fp_dst, "\tstd::stringstream src;\n\n");
	
	/********************
	********************/
	enum{
		BUF_SIZE = 500,
	};
	
	char buf[BUF_SIZE];
	while(fgets(buf, BUF_SIZE, fp_src) != NULL){
		std::string str_src = buf;
		
		/********************
		insert top
		********************/
		/*
		size_t pos;
		while((pos = str_src.find_first_of(" 　\t\n\r")) != std::string::npos){ // 半角・全角space, \t 改行 削除
			str_src.erase(pos, 1);
		}
		*/
		
		// 改行削除
		size_t pos;
		while((pos = str_src.find_first_of("\n\r")) != std::string::npos){
			str_src.erase(pos, 1);
		}
		
		// \tを変換
		while((pos = str_src.find_first_of("\t")) != std::string::npos){
			str_src.replace(pos, 1, "\\t");
		}
		
		// str_src = std::regex_replace(str_src, std::regex("\t"), "\\t");
		// str_src = std::regex_replace(str_src, std::regex("\n"), "\\n\n");
		
		/********************
		insert top
		********************/
		std::string str_top = "\tsrc << \"";
		str_src.insert(0, str_top);
		
		/********************
		insert end.
		********************/
		str_src += "\\n\";\n";
		
		/********************
		********************/
		fprintf(fp_dst, "%s", str_src.c_str());
	}	
	
	
	/********************
	********************/
	fprintf(fp_dst, "\n\treturn src.str();\n");
	
	
	/********************
	********************/
	fclose(fp_src);
	fclose(fp_dst);
	
	printf("Good-bye\n");
	
	return 0;
}
