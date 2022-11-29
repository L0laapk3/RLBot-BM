#pragma once

#include <limits>



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
	bool hasValue() const {
		return value != T::markedValue();
	}
	void clear() {
		value = T::markedValue();
	}
};