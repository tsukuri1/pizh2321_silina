from pizza import PizzaItem
from order import CustomerOrder
import datetime

class RestaurantTerminal: # Терминал заказов с расширенным функционалом
    
    def __init__(self):
        self.menu = self._initialize_menu()
        self.today_special = "Пепперони"
    
    def _initialize_menu(self): # Инициализация меню с сезонными предложениями
        return {
            1: PizzaItem("Пепперони", 850, ["салями", "сыр моцарелла", "томатный соус"]),
            2: PizzaItem("Грибная", 790, ["шампиньоны", "сливочный соус", "пармезан"]),
            3: PizzaItem("Вегетарианская", 920, ["перец", "помидоры", "оливки", "руккола"]),
            4: PizzaItem("С морепродуктами", 1100, ["креветки", "мидии", "чеснок", "лимон"])
        }
    
    def show_menu(self): # Отображение упрощенного меню
        print("\nМеню:")
        for num, pizza in self.menu.items():
            print(f"{num}. {pizza.name}: {pizza.price} руб ({', '.join(pizza.ingredients)})")
    
    def create_order(self): # Создание заказа с обработкой ввода
        order = CustomerOrder()
        order.order_time = datetime.datetime.now()
        
        while True:
            self.show_menu()
            choice = input("\nВыберите пиццу (номер) или 'завершить': ")
            
            if choice.lower() in ['завершить', 'готово']:
                break
            
            try:
                selected = int(choice)
                if selected in self.menu:
                    chosen_pizza = self.menu[selected]
                    order.add_item(chosen_pizza)
                    print(f"\nДобавлено: {chosen_pizza.name}")
                else:
                    print("Пожалуйста, выберите номер из меню")
            except ValueError:
                print("Введите корректный номер или команду")
        
        return order
    
    def process_order(self, order): # Полная обработка заказа
        total = order.calculate_total()
        print(f"\nОбщая сумма заказа: {total} руб.")
        
        while True:
            try:
                payment = float(input("Введите сумму для оплаты: "))
                if payment >= total:
                    if payment > total:
                        print(f"Ваша сдача: {payment - total:.2f} руб.")
                    self._prepare_order(order)
                    break
                else:
                    print("Недостаточно средств. Попробуйте еще раз")
            except ValueError:
                print("Пожалуйста, введите числовое значение")
    
    def _prepare_order(self, order): # Процесс приготовления заказа
        print("\nПриступаем к приготовлению вашего заказа:")
        for item in order.items:
            item.prepare()
        print("\nСпасибо за заказ! Приятного аппетита!")