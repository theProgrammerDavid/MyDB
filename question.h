#pragma once
#ifndef QUESTION_H

#include <string>
enum options{ A,B,C,D, NOT_SELECTED};
using namespace std;

class question
{
public:

	bool question_has_image = false;
	bool option_a_has_image = false;
	bool option_b_has_image = false;
	bool option_c_has_image = false;
	bool option_d_has_image = false;

	bool isMarkedForReview = false;
	bool isMarkedForAnswer = false;

	std::string question_text;
	std::string option_a, option_b, option_c, option_d;

	std::string question_image = NULL;
	std::string option_a_image = NULL;
	std::string option_b_image = NULL;
	std::string option_c_image = NULL;
	std::string option_d_image = NULL;

	short unsigned int selected_option;
	short unsigned int correct_option;
	int questionNumber;

	int checkQuestionAnswer();

	//check size_t feasability
	void setQuestionImage(std::string data, size_t size);
	void setOptionAImage(std::string data, size_t size);
	void setOptionBImage(std::string data, size_t size);
	void setOptionCImage(std::string data, size_t size);
	void setOptionDImage(std::string data, size_t size);

	void setQuestionText(std::string txt);
	void setQuestionText(char *txt);
	
	void setOptionTexts(string a, string b, string c, string d);
	void setOptionTexts(char *a, char *b, char *c, char *d);

	void setQuestionNumber(int i);

	question(int i);
	~question();
};





#endif // !QUESTION_H

