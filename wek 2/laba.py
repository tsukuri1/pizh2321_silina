# Программирование на языке высокого уровня (Python).
# Задание week_02_02. Вариант 3
#
# Выполнила: Силина О.Р.
# Группа: ПИЖ-б-о-23-2(1)

import random

class ArrayOperations:
    def find_min(self, arr):
        if not arr:
            return None
        return min(arr)

    def find_max(self, arr):
        if not arr:
            return None
        return max(arr)

    def sum_elements(self, arr):
        return sum(arr)

    def sort_array(self, arr):
        return sorted(arr)

class TArray:
    def __init__(self, size=0, initial_value=None, from_array=None):
        self.__size = 0
        self.__data = []

        if from_array is not None:
            if isinstance(from_array, TArray):
                self.__size = from_array.__size
                self.__data = from_array.__data[:]
            else:
                raise TypeError("from_array должен быть типа TArray")
        elif size > 0:
            self.__size = size
            self.__data = [initial_value] * size if initial_value is not None else [None] * size
        self._operations = ArrayOperations()

    def __len__(self):
        return self.__size

    def __getitem__(self, index):
        if 0 <= index < self.__size:
            return self.__data[index]
        else:
            raise IndexError("Индекс вне диапазона")

    def __setitem__(self, index, value):
        if 0 <= index < self.__size:
            self.__data[index] = value
        else:
            raise IndexError("Индекс вне диапазона")

    def __add__(self, other):
        if not isinstance(other, (int, float)):
            raise TypeError("Можно добавлять только числа")

        new_array = TArray(size=self.__size + 1)
        for i in range(self.__size):
            new_array[i] = self.__data[i]
        new_array[self.__size] = other
        return new_array

    def __mul__(self, scalar):
        if not isinstance(scalar, (int, float)):
            raise TypeError("Scalar должен быть числом")

        new_array = TArray(size=self.__size)
        for i in range(self.__size):
            new_array[i] = self.__data[i] * scalar
        return new_array

    def __str__(self):
        return str(self.__data)

    def __call__(self, index):
        return self.__getitem__(index)

    def input_data(self):
        try:
            for i in range(self.__size):
                self.__data[i] = float(input(f"Введите элемент {i + 1}: "))
        except ValueError:
            print("Ошибка: Введите числовое значение.")

    def display_data(self):
        print(self)

    def find_min(self):
        return self._operations.find_min(self.__data)

    def find_max(self):
        return self._operations.find_max(self.__data)

    def sum_elements(self):
        return self._operations.sum_elements(self.__data)

    def sort_array(self):
        self.__data = self._operations.sort_array(self.__data)

    def get_data(self):
        return self.__data[:]

class SpecialArray(TArray):
    def __init__(self, size=0, initial_value=None):
        super().__init__(size, initial_value)

    def fill_random(self, min_value=0, max_value=100):
        for i in range(len(self)):
            self[i] = random.randint(min_value, max_value)

arr1 = TArray(5)
arr2 = TArray(3, 0)
arr3 = TArray(4, initial_value=1.5)

arr4 = TArray(from_array=arr2)

arr5 = TArray(3)
print("Введите элементы для arr5:")
arr5.input_data()
print("Массив arr5:", arr5)
arr5.display_data()

print(f"Элемент arr2 по индексу 1: {arr2[1]}")
arr2[1] = 10

arr6 = arr2 + 5
arr7 = arr2 * 2
print(f"arr6 (arr2 + 5): {arr6}")
print(f"arr7 (arr2 * 2): {arr7}")

print(f"Минимум в arr2: {arr2.find_min()}")
print(f"Максимум в arr2: {arr2.find_max()}")
print(f"Сумма элементов в arr2: {arr2.sum_elements()}")
arr2.sort_array()
print(f"Отсортированный arr2: {arr2}")

print(f"Элемент arr2 по индексу 0 (с использованием __call__): {arr2(0)}")

special_arr = SpecialArray(5)
special_arr.fill_random()
print(f"Специальный массив, заполненный случайными числами: {special_arr}")