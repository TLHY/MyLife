#pragma once
#include "tag_parents.h"
#include <vector>

class TagBundle
{
public:
	std::vector<Tag*> tags;	// ���� �Ҵ�� Tag�� �����ϴ� vector

	// ������
	TagBundle() : tags() {};
	TagBundle(std::vector<Tag*>& tags);
	TagBundle(const TagBundle& old);
	TagBundle(TagBundle&& old);
	
	// ���� ������
	TagBundle& operator=(const TagBundle& other);
	TagBundle& operator=(TagBundle&& other);
	
	/* ��Ģ �˻�
		_tags�� ���Ե� Tag�鿡 ���� Tag.Validate()�� ȣ���մϴ�.
	*/
	void Validate() const;

	/* ��� �Լ�
		_tags�� ���Ե� Tag�鿡 ���� Tag.Print()�� ȣ���մϴ�.
	*/
	void Print() const;

	/* Ŭ������ �±׸� ã�� �Լ�
		Ư�� Ŭ������ ����� Tag�� ���ο� TagBundle�� ��� ��ȯ�մϴ�.
		���� ���, GetTagByType<BookTag>()�� BookTag�� ����ϴ� Tag�� �����ϴ� ���ο� TagBundle�� ��ȯ�մϴ�.
	*/
	template<typename T> TagBundle GetTagByType();
	
	// �ı���
	~TagBundle();
};

// ostream�� ���� left-shift ����; ��� �Լ� ���
inline std::ostream& operator<<(std::ostream& out, const TagBundle& tag_bundle) {
	tag_bundle.Print();
	return out;
}

/* ��� ���θ� Ȯ���ϴ� �Լ�
	�����Ͱ� ����Ű�� ��ü�� ������ Ŭ������ ����ߴ��� �˻��մϴ�.
	TagBundle::GetTagByType<T>()������ ����մϴ�. 
*/
template<typename Base, typename T> bool instanceof(const T* ptr) {
	return dynamic_cast<const Base*>(ptr) != nullptr;
}

template<typename T> TagBundle TagBundle::GetTagByType()
{
	std::vector<Tag*> found;
	Tag* cur;
	for (unsigned int i = 0; i < tags.size(); i++) {
		cur = tags.at(i);
		if (instanceof<T>(cur)) {
			found.push_back(cur->copy());
		}
	}
	return TagBundle(found);
}
