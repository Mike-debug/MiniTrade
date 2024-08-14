//
// Created by Mike_Wei on 5/5/2024.
//

#ifndef MINITRADE_SYNC_H
#define MINITRADE_SYNC_H

#include <mutex>
#include <condition_variable>

extern std::mutex m_mutex;
extern std::condition_variable cv;
extern bool ready1;

#endif //MINITRADE_SYNC_H
