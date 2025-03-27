# Программирование на языке высокого уровня (Python).
# Задание week_04_03_02. Вариант 3
#
# Выполнила: Силина О.Р.
# Группа: ПИЖ-б-о-23-2(1)
from terminal import RestaurantTerminal

def run_pizzeria():
    # Главная функция запуска пиццерии
    terminal = RestaurantTerminal()
    try:
        customer_order = terminal.create_order()
        if customer_order.items:
            terminal.process_order(customer_order)
        else:
            print("Ваш заказ пуст. Возвращайтесь, когда решите что заказать!")
    except KeyboardInterrupt:
        print("\nРабота терминала завершена")

if __name__ == "__main__":
    run_pizzeria()