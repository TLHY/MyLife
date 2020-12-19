#include "TagBundle.h"

TagBundle::TagBundle(std::vector<Tag*>& tags_)
	: TagBundle()
{
	tags.insert(tags.begin(), tags_.begin(), tags_.end());
}

TagBundle::TagBundle(const TagBundle& old) : TagBundle()
{
	for (unsigned int i = 0; i < old.tags.size(); i++) {
		tags.push_back(old.tags.at(i)->copy());
	}
}

TagBundle::TagBundle(TagBundle&& old) : TagBundle(old.tags)
{
	old.tags.clear();
}

TagBundle& TagBundle::operator=(const TagBundle& other)
{
	for (unsigned int i = 0; i < tags.size(); i++) {
		delete tags.at(i);
	}
	tags.clear();
	for (unsigned int i = 0; i < other.tags.size(); i++) {
		tags.push_back(other.tags.at(i)->copy());
	}
	return *this;
}

TagBundle& TagBundle::operator=(TagBundle&& other)
{
	for (unsigned int i = 0; i < tags.size(); i++) {
		delete tags.at(i);
	}
	tags.clear();
	tags.insert(tags.begin(), other.tags.begin(), other.tags.end());
	other.tags.clear();
	return *this;
}


void TagBundle::Validate() const
{
	for (unsigned int i = 0; i < tags.size(); i++) {
		tags.at(i)->Validate();
	}
}

void TagBundle::Print() const
{
	for (unsigned int i = 0; i < tags.size(); i++) {
		tags.at(i)->Print();
		std::cout << "\n";
	}
}

TagBundle::~TagBundle()
{	
	while (!tags.empty()) {
		tags.pop_back();
	}

}
