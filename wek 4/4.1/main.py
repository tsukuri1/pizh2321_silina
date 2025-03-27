# Программирование на языке высокого уровня (Python).
# Задание week_04_01. Вариант 3
#
# Выполнила: Силина О.Р.
# Группа: ПИЖ-б-о-23-2(1)

from deposits import TermDeposit, BonusDeposit, CapitalizationDeposit

def get_float_input(prompt):
    # Функция для безопасного ввода чисел с плавающей точкой
    while True:
        try:
            return float(input(prompt))
        except ValueError:
            print("Ошибка! Введите число.")

def main():
    print("Банковские вклады - калькулятор прибыли")
    print("---------------------------------------")
    
    # Ввод основных параметров
    amount = get_float_input("Введите сумму вклада (руб): ")
    months = int(get_float_input("Введите срок вклада (мес): "))
    rate = get_float_input("Введите годовую процентную ставку (%): ")

    # Выбор типа вклада
    print("\nВыберите тип вклада:")
    print("1. Срочный вклад (простые проценты)")
    print("2. Бонусный вклад (дополнительный % при большой сумме)")
    print("3. Вклад с капитализацией процентов")
    
    choice = input("Ваш выбор (1-3): ")

    # Создание соответствующего вклада
    if choice == "1":
        deposit = TermDeposit(amount, months, rate)
    elif choice == "2":
        threshold = get_float_input("Введите минимальную сумму для бонуса (руб): ")
        bonus = get_float_input("Введите бонусный процент (% от прибыли): ")
        deposit = BonusDeposit(amount, months, rate, threshold, bonus)
    elif choice == "3":
        deposit = CapitalizationDeposit(amount, months, rate)
    else:
        print("Неверный выбор!")
        return

    # Расчет и вывод результата
    profit = deposit.calculate_profit()
    total = amount + profit
    
    print("\nРезультаты расчета:")
    print(f"Сумма вклада: {amount:.2f} руб.")
    print(f"Срок: {months} мес.")
    print(f"Процентная ставка: {rate:.2f}% годовых")
    print(f"Ожидаемая прибыль: {profit:.2f} руб.")
    print(f"Итоговая сумма: {total:.2f} руб.")

if __name__ == "__main__":
    main()