//
// Created by dianh on 2021/04/16.
//

#ifndef SWIN_TRANSFORMER_CPP_TENSOR_H
#define SWIN_TRANSFORMER_CPP_TENSOR_H

#include <bits/stdc++.h>

#include <libpmem.h>
#ifdef _PERSISTENT_TENSOR
	void *pop = nullptr, *now;
#endif
namespace shift_window_transformer {
    typedef std::vector<int> TensorShape;

    template<typename T>
    class Tensor : public std::vector<T> {
    public:
        Tensor() : std::vector<T>() {
        }

        Tensor(int size, T default_data) : std::vector<T>(size, default_data) {
            shape.clear();
            shape.push_back(size);
        }

        TensorShape shape;

#ifdef _PERSISTENT_TENSOR
		void * operator new(size_t size) {
			if(pop == nullptr)
			{
				pop = pmem_map_file("/mnt/ramdisk/swin", (1 << 30), PMEM_FILE_CREATE, 0x660, NULL, NULL);
				if(pop == NULL)
				{
					perror("pmem_map_file");
					return pop;
				}
				now = pop;
			}

			void *toRet = now;
			now = (void*) (((char*) now) + size);
			std::cout << "Allocating on PMEM " << size << " @ " << toRet << std::endl;
			return toRet;
		}

		void operator delete(void *p)
		{
			std::cout << "Free PMEM: " << p << std::endl;
		}
#endif

        friend std::ostream &operator<<(std::ostream &os, const Tensor<T> &vec) {
            int cnt = 1;
            os << "[" << vec.size() << "]";
            os << "[";
            for (auto i = 0; i < vec.shape.size(); ++i) {
                if (i)
                    os << ", ";
                os << vec.shape[i];
                cnt *= vec.shape[i];
            }
            os << "]";
            assert(cnt == vec.size());
            return os;
        }
    };
}

#endif //SWIN_TRANSFORMER_CPP_TENSOR_H
