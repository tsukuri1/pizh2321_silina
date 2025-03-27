class CustomerOrder:  # Класс для управления заказом клиента с расширенной функциональностью
    
    def __init__(self):
        self.items = []
        self.order_time = None
        self.status = "Новый"
    
    def add_item(self, pizza_item):  # Добавляет пиццу в заказ
        self.items.append(pizza_item)
        self.status = "Обновлен"
    
    def calculate_total(self):  # Рассчитывает итоговую сумму с возможной скидкой
        base_sum = sum(item.price for item in self.items)
        discount = 0.9 if len(self.items) > 2 else 1.0  # 10% скидка на 3+ пиццы
        return int(base_sum * discount)
    
    def __str__(self):  # Детализированное представление заказа
        if not self.items:
            return "Ваш заказ пока пуст"
        
        receipt = ["\nВаш заказ:"]
        receipt.extend(f"• {item}" for item in self.items)
        receipt.append(f"\nИтого к оплате: {self.calculate_total()} руб.")
        return "\n".join(receipt)