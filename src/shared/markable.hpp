#pragma once

#include <limits>
#include <cmath>



struct MarkableFloat {
	typedef float ValueType;
	static constexpr float markedValue() noexcept { return std::numeric_limits<float>::quiet_NaN(); }
	static constexpr bool isMarked(float value) noexcept { return std::isnan(value); }
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
		return !T::isMarked(value);
	}
	void clear() {
		value = T::markedValue();
	}
};