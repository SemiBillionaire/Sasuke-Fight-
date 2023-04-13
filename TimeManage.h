#ifndef TIME_MANAGE_H_
#define TIME_MANAGE_H_

class Time
{
public:
	Time();
	~Time();
	void begin();
	void end();
	void pause();
	void unpause();
	int get_time();
	bool game_started();
	bool game_paused();
private:
	int begin_time;
	int paused_time;
	bool paused_;
	bool started_;

};

#endif
