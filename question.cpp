#include "question.h"




int question::checkQuestionAnswer()
{
	

		if (selected_option == correct_option) {
			return 1;
		}

		else if (selected_option == NOT_SELECTED) {
			return 0;
		}

		else return -1;
	
}

void question::setQuestionImage(std::string data, size_t size)
{
	question_image.resize(size);
	question_image = data;
}

void question::setOptionAImage(std::string data, size_t size)
{
	option_a_image.resize(size);
	option_a_image = data;
}

void question::setOptionBImage(std::string data, size_t size)
{
	option_b_image.resize(size);
	option_b_image = data;
}

void question::setOptionCImage(std::string data, size_t size)
{
	option_c_image.resize(size);
	option_c_image = data;
}

void question::setOptionDImage(std::string data, size_t size)
{
	option_d_image.resize(size);
	option_d_image = data;
}

void question::setQuestionText(std::string txt)
{
	question_text = txt;
}

void question::setQuestionText(char * txt)
{
	question_text = txt;
}

void question::setQuestionNumber(int i)
{
	questionNumber = i;
}

question::question(int i) {

	isMarkedForReview = false;
	questionNumber = i;

}

question::~question()
{
}

void question::setOptionTexts(string a, string b, string c, string d) {
	option_a = a;
	option_b = b;
	option_c = c;
	option_d = d;
}

void question::setOptionTexts(char * a, char * b, char * c, char * d)
{
	option_a = a;
	option_b = b;
	option_c = c;
	option_d = d;
}
