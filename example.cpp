#include <iostream>
#include <chrono>
#include <thread>

#include "threadpool.h"

//using uLong = unsigned long long;
typedef unsigned long long uLong;
class MyTask : public Task
{
public:
	MyTask(int begin, int end)
		: begin_(begin)
		, end_(end)
	{}
	Any run()
	{
		std::cout << "tid:" << std::this_thread::get_id() << "begin!" << std::endl;
		std::this_thread::sleep_for(std::chrono::seconds(3));
		
		uLong sum = 0;
		for (uLong i = begin_; i <= end_; i++)
		{
			sum += i;
		}
		std::cout << "tid:" << std::this_thread::get_id() << "end!" << std::endl;
		return sum;
	}
private:
	int begin_;
	int end_;
};

int main()
{
	{
		ThreadPool pool;
		pool.start(4);
		Result res1 = pool.submitTask(std::make_shared<MyTask>(1, 10000000));
		uLong sum1 = res1.get().cast_<uLong>();
		std::cout << sum1 << std::endl;
	}
	std::cout << "main over" << std::endl;
	getchar();
#if 0                         
	// 问题：ThreadPool对象析构以后，怎么样把线程相关的线程资源全部回收
	{
		ThreadPool pool;
		pool.setMode(PoolMode::MODE_CACHED);
		pool.start(4);

		Result res1 = pool.submitTask(std::make_shared<MyTask>(1, 10000000));
		Result res2 = pool.submitTask(std::make_shared<MyTask>(10000001, 20000000));
		Result res3 = pool.submitTask(std::make_shared<MyTask>(20000001, 30000000));
		pool.submitTask(std::make_shared<MyTask>(20000001, 30000000));
		pool.submitTask(std::make_shared<MyTask>(20000001, 30000000));
		pool.submitTask(std::make_shared<MyTask>(20000001, 30000000));

		uLong sum1 = res1.get().cast_<uLong>();
		uLong sum2 = res2.get().cast_<uLong>();
		uLong sum3 = res3.get().cast_<uLong>();

		std::cout << (sum1 + sum2 + sum3) << std::endl;

		/*pool.submitTask(std::make_shared<MyTask>());
		pool.submitTask(std::make_shared<MyTask>());
		pool.submitTask(std::make_shared<MyTask>());
		pool.submitTask(std::make_shared<MyTask>());
		pool.submitTask(std::make_shared<MyTask>());
		pool.submitTask(std::make_shared<MyTask>());
		pool.submitTask(std::make_shared<MyTask>());
		pool.submitTask(std::make_shared<MyTask>());
		pool.submitTask(std::make_shared<MyTask>());
		pool.submitTask(std::make_shared<MyTask>());*/
	}

	getchar();

#endif
}

