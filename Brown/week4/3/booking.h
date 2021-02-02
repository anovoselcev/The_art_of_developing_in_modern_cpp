#pragma once

#include <utility>

namespace RAII {

	template <typename Provider>
	class Booking {
	public:
		Booking(Provider* p,
				int count) : _provider(p), _count(count){}

		Booking(const Booking&) = delete;

		Booking(Booking&& book) : _provider(book._provider), _count(book._count) {
			book._provider = nullptr;
		}

		Booking& operator=(const Booking&) = delete;

		Booking& operator=(Booking&& book) {
			std::swap(book._provider, _provider);
			std::swap(book._count, _count);
			return *this;
		}

		~Booking() {
			if(_provider)
				_provider -> CancelOrComplete(*this);
		}
	private:
		Provider* _provider = nullptr;
		int _count = 0;
	};

}