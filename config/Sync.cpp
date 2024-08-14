#include"Sync.h"
std::mutex m_mutex;
std::condition_variable cv;
bool ready1 = false;
