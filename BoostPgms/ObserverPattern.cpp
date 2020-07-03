
#include <boost\signals2.hpp>
#include <string>
#include <iostream>
#include <boost\bind.hpp>

class NewsProducer {
public:
	using NewsUpdate = boost::signals2::signal<void(const std::string&)>;
	using NewsSubscriber = NewsUpdate::slot_type;

	boost::signals2::connection AddSubscriber(const NewsSubscriber& subscriber) {
		return m_newsUpdate.connect(subscriber);
	}
	void Publish(const std::string& news) {
		m_newsUpdate(news);
	}
private:
	NewsUpdate m_newsUpdate;
};

class NewsConsumer {
public:
	NewsConsumer(const std::string& cname, NewsProducer& producer) : m_consumerName(cname) {
		m_newsProducerConnection = producer.AddSubscriber(boost::bind(&NewsConsumer::HandleNewsUpdate, this, boost::placeholders::_1));
	}
	~NewsConsumer() {
		m_newsProducerConnection.disconnect();
	}

	void BlockSubscription() {
		m_block = m_newsProducerConnection;
	}

	void UnblockSubscription() {
		m_block.unblock();
	}

private:
	void HandleNewsUpdate(const std::string& news) const {
		std::cout << m_consumerName << " : " << news << "\n";
	}
private:
	std::string m_consumerName;
	boost::signals2::connection m_newsProducerConnection;
	boost::signals2::shared_connection_block m_block;
};

//int main() {
//
//	NewsProducer producer;
//
//	NewsConsumer subscriber1("Asianer", producer);
//	NewsConsumer subscriber2("Reporter", producer);
//	NewsConsumer subscriber3("Flowers", producer);
//
//	producer.Publish("Good Morning");
//
//	std::cout << "------------------------------------------\n";
//
//	subscriber2.BlockSubscription();
//	producer.Publish("Have a good day..!!");
//	subscriber2.UnblockSubscription();
//
//	std::cout << "------------------------------------------\n";
//
//	producer.Publish("Thank You..!!");
//}