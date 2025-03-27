# Программирование на языке высокого уровня (Python).
# Задание week_04_02. Вариант 3
#
# Выполнила: Силина О.Р.
# Группа: ПИЖ-б-о-23-2(1)

from complex import Complex

# Простые числа для демонстрации
num1 = Complex(1, 1)  # 1 + 1i
num2 = Complex(2, -1)  # 2 - 1i
num3 = Complex.from_string("3+2i")

print(f"Число 1: {num1}")
print(f"Число 2: {num2}")
print(f"Число 3: {num3}")

# Демонстрация операций
print("\nСложение:", num1 + num2)
print("Вычитание:", num1 - num2)
print("Умножение:", num1 * num2)

# Работа с файлами
num1.save("num1.json")
loaded_num = Complex.load("num1.json")
print("\nЗагруженное число:", loaded_num)