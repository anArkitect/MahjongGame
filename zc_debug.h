#pragma once

template<class T>
void debug(T value)
{
	std::cout << value << std::endl;
}

template<class T1, class T2>
void debug(T1 value1, T2 value2)
{
	std::cout << value1 << "  " << value2 << std::endl;
}

template<class T1, class T2, class T3>
void debug(T1 value1, T2 value2, T3 value3)
{
	std::cout << value1 << "  " << value2 << "  " << value3 << std::endl;
}

template<class T1, class T2, class T3, class T4>
void debug(T1 value1, T2 value2, T3 value3, T4 value4)
{
	std::cout << value1 << "  " << value2 << "  " << value3 << "  "  << value4 << std::endl;
}
