#include <cstdio>
#include <pthread.h>

// Дождаться в текущем потокеостальных потоков(из общего числа p)
void reduce_sum(int p)
{
	static pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER; // Объект сихронизации типа mutex
	static pthread_cond_t c_in = PTHREAD_COND_INITIALIZER; // Объект сихронизации типа condvar
	static pthread_cond_t c_out = PTHREAD_COND_INITIALIZER; // Объект сихронизации типа condvar
	static int t_in = 0; // Число пришедших в функцию задач
	static int t_out = 0; // Число ожидающих выхода из функции задач
	if (p <= 1) 
		return;
	pthread_mutex_lock(&m); // "захватить" mutex для работы с перемнными t_in и t_out
	t_in++; // увеличить на 1 количество прибывших в эту функцию задач
	if (t_in >= p) // проверяем количество прибывших задач
	{
		t_out = 0; // текущий поток пришел последним, устанавливаем начальное значение для t_out
		pthread_cond_broadcast(&c_in); // разрешаем остальным продолжать работу
	}
	else // есть еще не пришедшие потоки
	{
		while (t_in < p) // ожидаем, пока в эту функцию не придут все потоки
		{
			pthread_cond_wait(&c_in, &m); // ожидаем разрешения продолжить работу: освободить mutex и ждать сигнала от condvar, затем "захватить" mutex опять
		}
	}
	t_out++; // увеличить на 1 количество ожидающих выхода задач
	if (t_out >= p) // проверяем количесвто прибывших задач
	{
		t_in = 0; // текущий поток пришел в очередь последним, устанавливаем начальное значение для t_in
		pthread_cond_broadcast(&c_out); // разрешаем остальным продолжать работу
	}
	else // в очереди ожидания еще есть потоки
	{
		while (t_out < p) // ожидаем, пока в очередь ожидания не придет последний поток
		{
			pthread_cond_wait(&c_out, &m); // ожидаем разрешения продолжить работу: освободить mutex и ждать сигнала от condvar, затем "захватить" mutex опять
		}
	}
	pthread_mutex_unlock(&m); // освободить "mutex"
}
