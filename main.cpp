//
// Created by dianh on 2021/04/16.
//
#include <bits/stdc++.h>

#include "swin_transformer.h"
#include "linear.h"
#include "feed_forward.h"
#include "cyclic_shift.h"
#include "functions.h"
#include "tensor.h"
#include "patch_merging.h"
#include "window_attention.h"
#include "functions.h"
using namespace std;
typedef float data_t;
//auto *swin_t = new shift_window_transformer::SwinTransformer<data_t>(
//        96, std::array<int, 4>{2, 2, 6, 2},
//        std::array<int, 4>{3, 6, 12, 24});
//auto *swin_s = new shift_window_transformer::SwinTransformer<data_t>(
//        96, std::array<int, 4>{2, 2, 18, 2},
//        std::array<int, 4>{3, 6, 12, 24});
//auto *swin_b = new shift_window_transformer::SwinTransformer<data_t>(
//        96, std::array<int, 4>{2, 2, 18, 2},
//        std::array<int, 4>{4, 8, 16, 32});
//auto *swin_l = new shift_window_transformer::SwinTransformer<data_t>(
//        96, std::array<int, 4>{2, 2, 18, 2},
//        std::array<int, 4>{6, 12, 24, 48});

int main() {
    /*
     * Test Swin Transformer
     */
    try {
        std::cout << "Test Tiny Swin Transformer: ";
        std::cout.flush();
        auto *swin_t = new shift_window_transformer::SwinTransformer<data_t>(
                96, std::array<int, 4>{2, 2, 6, 2},
                std::array<int, 4>{3, 6, 12, 24});
        shift_window_transformer::Tensor<data_t> input(3 * 224 * 224, 0);
        input.shape = {3, 224, 224};
        shift_window_transformer::Tensor<data_t> output{};

		struct timespec begin, end;
		clock_gettime(CLOCK_REALTIME, &begin);
        swin_t->forward(input, output);
		clock_gettime(CLOCK_REALTIME, &end);

		long seconds = end.tv_sec - begin.tv_sec;
    	long nanoseconds = end.tv_nsec - begin.tv_nsec;

        delete swin_t;
        std::cout << "Ok" << std::endl;
		printf("%10ld s %10ld ns\n", seconds, nanoseconds);
    } catch (...) {
        std::cout << "Error" << std::endl;
    }
    return 0;
}

