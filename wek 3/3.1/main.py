# Программирование на языке высокого уровня (Python).
# Задание week_03_01. Вариант 3
#
# Выполнила: Силина О.Р.
# Группа: ПИЖ-б-о-23-2(1)

from roman import Roman

# Примеры использования:
num1 = Roman("XX")
num2 = Roman(3)

print(f"{num1} + {num2} = {num1 + num2}")
print(f"{num1} - {num2} = {num1 - num2}")
print(f"{num1} * {num2} = {num1 * num2}")
print(f"{num1} / {num2} = {num1 / num2}")

print(f"Римское представление числа 2003: {Roman.to_roman(2003)}")
print(f"Десятичное представление числа MMIII: {Roman.from_roman('MMIII')}")