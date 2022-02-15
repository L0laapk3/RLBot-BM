#pragma once

#include <limits>



namespace RLBotBM::Shared {

struct MarkableFloat {
	typedef float ValueType;
	static constexpr float markedValue() noexcept { return std::numeric_limits<float>::quiet_NaN(); }
};

template <typename T>
class Markable {
	typename T::ValueType value;
public:
	Markable(typename T::ValueType v) : value(v) {}
	Markable() : Markable(T::markedValue()) {}
	Markable(const Markable<T>& other) : value(other.value) {}
	Markable& operator=(const Markable& other) {
		value = other.value;
		return *this;
	}
	Markable& operator=(typename T::ValueType v) {
		value = v;
		return *this;
	}
	operator typename T::ValueType() const {
		return value;
	}
	bool isNull() const {
		return value == T.markedValue();
	}
	void mark() {
		value = T.markedValue();
	}
};

}