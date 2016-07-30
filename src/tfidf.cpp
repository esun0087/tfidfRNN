#include <unordered_set>
#include <unordered_map>
#include <fstream>
#include <string>
#include <cstring>
#include <sstream>
#include <iostream>
#include <cmath>

int argPos(char *str, int argc, char **argv)
{
    int a;
    
    for (a=1; a<argc; a++) if (!strcmp(str, argv[a])) return a;
    
    return -1;
}

int main(int argc, char **argv)
{
	char *input, *output;
	int i = argPos((char*)"-input",argc,argv);
	input = argv[i+1];
	i = argPos((char*)"-output",argc,argv);
	output = argv[i+1];
std::unordered_map<std::string,float> t;
	std::unordered_map<std::string,float> tf_idf;
	std::unordered_map<std::string, float> idf;
	int lc,wc,idf_f,tf_f,tfidf_f,df_f;
	tfidf_f=argPos((char*)"-tfidf",argc,argv);
	idf_f=argPos((char*)"-idf",argc,argv);
	tf_f=argPos((char*)"-tf",argc,argv);
	df_f=argPos((char*)"-df",argc,argv);
	std::ifstream in(input);
	std::string line;
	
	while (std::getline(in,line))
	{
		std::string word;
		std::stringstream ss(line);
		std::unordered_set<std::string> tmp;
		while (ss >> word)
		{
			tf_idf[word]++;
			tmp.insert(word);
			wc++;
		}
		lc++;
		for (auto &j:tmp)
		{
			idf[j]++;
		}
	}
	//printf("%lu\n", idf.size());
	
	if (tfidf_f>0)
		for (auto &j:idf)
			tf_idf[j.first] = (j.second/(float)wc)*(log10((float)lc/j.second));
	if (tf_f>0)
		for (auto &j:tf_idf)
			tf_idf[j.first]=j.second/(float)wc;

	if (idf_f>0)
		for (auto &j:idf)
			tf_idf[j.first] = (log10((float)lc/j.second));
	if (df_f>0)
		for (auto &j:idf)
			tf_idf[j.first] = (j.second/(float)lc);
	
	std::ofstream out(output);
	for (auto &j:tf_idf)
		out << j.first << " " << j.second << '\n';
	out.close();
}