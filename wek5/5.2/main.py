# Программирование на языке высокого уровня (Python).
# Задание week_05_2. Вариант 3
#
# Выполнил: Силина О.Р.
# Группа: ПИЖ-б-о-23-2(1)

from transport import *

def main():
    # Создаем транспортные средства
    boat = VodnoeTS("Катер")
    car = Avtomobil("Toyota")

    # Тестируем водный транспорт
    boat.start_engine()
    boat.move(20)  # не поедет - якорь опущен
    boat.raise_anchor()
    boat.move(30)
    boat.stop_engine()

    # Тестируем автомобиль
    car.start_engine()
    car.move(80)
    car.refuel(50)
    car.move(100)
    car.stop_engine()

if __name__ == "__main__":
    main()