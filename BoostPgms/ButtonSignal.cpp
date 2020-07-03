
#include <boost\signals2.hpp>
#include <iostream>
#include <boost\function.hpp>

class Button {
public:
	using ButtonClicked = boost::signals2::signal<void(const std::string& caption)>;
	using ListenerType = ButtonClicked::slot_type;

	boost::signals2::connection AddListener(const ListenerType& listener) {
		return m_buttonClicked.connect(listener);
	}
	Button(const std::string& name) : m_buttonName(name){}

	void Clicked() {
		m_buttonClicked(m_buttonName);
	}

private:
	ButtonClicked m_buttonClicked;
	std::string m_buttonName;
};

class Listener {
public:
	Listener(const std::string& listenerName, Button& button) :
		m_listenerName(listenerName) {
		m_connection = button.AddListener(boost::bind(&Listener::PerformAction, this, boost::placeholders::_1));
	}
	~Listener() {
		m_connection.disconnect();
	}
	void Block() {
		m_block = m_connection;
	}
	void Unblock() {
		if(m_connection.blocked())
			m_block.unblock();
	}
private:
	void PerformAction(const std::string& buttonID) {
		std::cout << m_listenerName << " - This is from Button : " << buttonID << "\n";
	}

private:
	std::string m_listenerName;
	boost::signals2::connection m_connection;
	boost::signals2::shared_connection_block m_block;
};

int main() {
	Button btn("btnChangeLayout");

	Listener l1("Font", btn);
	Listener l2("Layout", btn);
	Listener l3("Color", btn);

	btn.Clicked();
}