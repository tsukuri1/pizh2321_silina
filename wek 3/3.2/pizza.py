class PizzaItem:  # Усовершенствованный класс пиццы с дополнительными атрибутами
    
    def __init__(self, name, price, ingredients, size="L"):
        self.name = name
        self.price = price
        self.ingredients = ingredients
        self.size = size
        self.prep_time = 10 + len(ingredients) * 2  # Время приготовления
    
    def prepare(self): # Процесс приготовления с подробным выводом
        print(f"\nНачинаем готовить {self.name}...")
        print(f"Ингредиенты: {', '.join(self.ingredients)}")
        print(f"Примерное время приготовления: {self.prep_time} минут")
    
    def __str__(self): # Форматированное описание пиццы
        return f"{self.name} ({self.size}): {self.price} руб. ({', '.join(self.ingredients)})"