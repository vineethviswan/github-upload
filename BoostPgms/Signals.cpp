
#include <string>
#include <boost\signals2.hpp>
#include <iostream>
#include <memory>
#include <boost\smart_ptr.hpp>
#include <algorithm>
#include <boost\bind.hpp>

template<typename T>
class INotifyPropertyChanged {
public:
	boost::signals2::signal<void(const T*, std::string)> PropertyChanged;
};

class Player : public INotifyPropertyChanged<Player> {
public:
	Player(const char* n, int a) : m_name(n), m_age(a), m_goals(0) {}

	boost::signals2::signal<void(std::string)> Scores;

	void SetAge(int val) {
		if (val == m_age) return;
		m_age = val;
		PropertyChanged(this, std::string("Age"));
	}
	std::string GetName()const {
		return m_name;
	}
	int GetAge() const {
		return m_age;
	}

	void Score() {
		++m_goals;
		Scores(m_name);
	}

private:
	int m_age;
	std::string m_name;
	int m_goals;
};

class Coach {
public:
	void PlayerScored(std::string name) {
		std::cout << "Well done, " << name << "\n";
	}
};

void Third() {
	std::cout << "This is Third()..\n";
}


void ScopedConnection() {

	boost::signals2::signal<void()> s;
	s.connect(Third);
	{
		auto cn = s.connect(1, []() {std::cout << "First..\n"; });
		boost::signals2::scoped_connection sc(cn);
		s.connect(0, []() { std::cout << "Second..\n"; });
		s();
	}
	std::cout << "---------------------------------\n";
	s.disconnect(Third);
	s();
}

template<typename T>
class Average {
public:
	typedef T result_type;

	template<typename InputItr>
	T operator()(InputItr first, InputItr last) const {
		if (first == last) return T();
		float sum = 0.0;
		int count = 0;
		while (first != last)
		{
			sum += *first++;
			count++;
		}
		return sum / count;
	}
};

template<typename T> 
class ReturnAll {
public:
	typedef T result_type;

	template<typename InputItr>
	T operator()(InputItr first, InputItr last) const {
		return T(first, last);
	}
};

void SignalReturnedValues() {

	boost::signals2::signal<float(float, float), Average<float>> sng;

	sng.connect([](float a, float b) {return a + b; });
	sng.connect([](float a, float b) {return a * b; });

	std::cout << sng(3.0, 4.0) << "\n";

	boost::signals2::signal<float(float, float), ReturnAll<std::vector<float>>> s_all;

	s_all.connect([](float a, float b) {return a + b; });
	s_all.connect([](float a, float b) {return a * b; });

	std::vector<float> v = s_all(3, 4);
	for (auto& itr : v)
		std::cout << itr << " ";

}

//int main() {
//
//	Player p1("Vijay", 25);
//
//	//p1.PropertyChanged.connect([](const Player* pl, std::string ppty) {
//	//	std::cout << pl->GetName() << "'s " << ppty << " has been changed to " << pl->GetAge() << "\n";
//	//	});
//
//	//p1.SetAge(26);
//	//
//	std::unique_ptr<Coach> ch = std::make_unique<Coach>();
//	p1.Scores.connect(std::bind(&Coach::PlayerScored, ch.get(), std::placeholders::_1));
//	{
//		auto ch2 = boost::make_shared<Coach>();
//		p1.Scores.connect(boost::signals2::signal<void(std::string)>::slot_type
//		(&Coach::PlayerScored, ch2.get(), boost::placeholders::_1).track(ch2));
//	}
//	
//	p1.Score();
//
//	//ScopedConnection();
//
//	//SignalReturnedValues();
//}