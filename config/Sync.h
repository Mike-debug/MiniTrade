//
// Created by Mike_Wei on 5/5/2024.
//

#ifndef MINITRADE_SYNC_H
#define MINITRADE_SYNC_H

#include <mutex>
#include <condition_variable>

std::mutex m_mutex;
std::condition_variable cv;
bool ready1 = false;

#endif //MINITRADE_SYNC_H
