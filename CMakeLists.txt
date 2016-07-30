add_definitions(-w -ffast-math -lm -lpthread -O3 -funroll-loops -std=c++11)

add_executable(rnnlm
	src/rnnlm.cpp
	src/rnnlmlib.cpp
)

add_executable(tfidf
			   src/tfidf.cpp
)
