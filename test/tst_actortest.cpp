#include <QtTest>
#include <QCoreApplication>

#include "testactor.h"
#include <actormanager.h>

// add necessary includes here

class actortest : public QObject
{
    Q_OBJECT

public:
    actortest();
    ~actortest();

private slots:
    void initTestCase();
    void cleanupTestCase();
    void slotIsCalledWhenMessageIsSend();

private:
    TestActor* actorA_;
    TestActor* actorB_;

};

actortest::actortest()
{

}

actortest::~actortest()
{

}

void actortest::initTestCase()
{
    actorA_ = ActorManager::instance()->spawn<TestActor>();
    actorB_ = ActorManager::instance()->spawn<TestActor>();
}

void actortest::cleanupTestCase()
{
    // ActorManager::kill(actorA_);
    // ActorManager::kill(actorB_);
}

void actortest::slotIsCalledWhenMessageIsSend()
{
    int arg = 10;
    QVERIFY(actorA_->testSend(actorB_, "updateIntProperty", arg));
    QVERIFY(actorB_->property("intProperty").canConvert<int>());
    QCOMPARE(actorB_->property("intProperty").toInt(), arg);
}

QTEST_MAIN(actortest)

#include "tst_actortest.moc"
