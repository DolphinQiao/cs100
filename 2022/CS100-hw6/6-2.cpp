#include <iostream>
#include <string>
#include <vector>

class Alarm{
public:
  // Your constructors and destructor.
  Alarm(int hour,int minute,std::string name) : m_set_hour(hour), m_set_minute(minute), m_name(name) {}
  virtual void Trigger() = 0;
  // ...
  const int get_set_hour()const{
    return m_set_hour;
  }
  const int get_set_minute()const{
    return m_set_minute;
  }

protected:
  // Declare protected members so that child classes have access to them.
  int m_set_hour,m_set_minute;
  std::string m_name;
};

class AlarmClock{
public:
  // Your constructors and destructor.
  AlarmClock():m_hour(0),m_minute(0){}
  ~AlarmClock();
  void AddAlarm(Alarm* alarm);
  void Input();
  void TimeElapse();
  // ...

private:
  std::vector<Alarm*> m_alarms;
  int m_hour,m_minute;
};
AlarmClock::~AlarmClock()
{
  for(std::vector<Alarm*>::iterator it=m_alarms.begin();it!=m_alarms.end();++it)
  {
    delete *it;
  }
}


class RepeatableAlarm:public Alarm{
  public:
  RepeatableAlarm(int hour,int minute,std::string name);
  virtual void Trigger(){
    std::cout<<m_name<<"    "<<m_set_hour<<":"<<m_set_minute<<std::endl;
  }
};

RepeatableAlarm::RepeatableAlarm(int hour,int minute,std::string name) : Alarm(hour, minute, name){}

class SnoozeableAlarm:public Alarm{
  public:
  SnoozeableAlarm(int,int,std::string);
  virtual void Trigger(){
    std::cout<<m_name<<"    "<<m_set_hour<<":"<<m_set_minute<<std::endl;
    std::cout<<"Do you want to snooze?";
    std::string s;
    std::cin>>s;
    if(s=="Y")
    {
      m_set_minute+=10;
    }else
    {
      delete this;
    }

  }
};

SnoozeableAlarm::SnoozeableAlarm(int hour,int minute,std::string name) : Alarm(hour,minute,name){}

/**************** Implementations ******************/
void AlarmClock::AddAlarm(Alarm* alarm) {
  m_alarms.push_back(alarm);
}

void AlarmClock::Input() {
  int n;
  std::cin>>n;
  for(int i=1;i<=n;++i)
  {
    std::string s;
    std::cin>>s;
    if(s=="R")
    {
      std::string s1,s2;
      std::cin>>s1>>s2;
      int min,hou;
      hou=int((s1[0]-'0')*10+s1[1]-'0');
      min=int((s1[3]-'0')*10+s1[4]-'0');
      // RepeatableAlarm a(hou,min,s2);
      // AddAlarm(&a);
      AddAlarm(new RepeatableAlarm(hou, min, s2));
    }else
    {
      std::string s1,s2;
      std::cin>>s1>>s2;
      int min,hou;
      hou=(s1[0]-'0')*10+s1[1]-'0';
      min=(s1[3]-'0')*10+s1[4]-'0';
      //SnoozeableAlarm a(hou,min,s2);
      AddAlarm(new SnoozeableAlarm(hou,min,s2));
    }
  }
}

void AlarmClock::TimeElapse() {
  m_minute++;
  if(m_minute==60)
  {
    m_minute=0;
    m_hour++;
  }
  if(m_hour==24)
  {
    m_hour=0;
    m_minute=0;
  }
  //std::cout<<m_hour<<' '<<m_minute<<std::endl;
  for(std::vector<Alarm*>::iterator it=m_alarms.begin();it!=m_alarms.end();++it)
  {
    //std::cout<<(*it)->get_set_hour()<<' '<<(*it)->get_set_minute()<<std::endl;
    if((*it)->get_set_hour()==m_hour && (*it)->get_set_minute()==m_minute)
    {
      //std::cout<<"A\n";
      (*it)->Trigger();
    }
  
  }
  return;
}

// ...

int main() {
  AlarmClock clock;
  for (int days = 0; days < 3; days++) {
    std::cout << "Do you want to add any alarms?" << std::endl;
    clock.Input();
    for (int minute = 0; minute < 24 * 60; minute++) {
      clock.TimeElapse();
    }
    std::cout << "A day has elapsed." << std::endl;
  }
  clock.~AlarmClock();
}