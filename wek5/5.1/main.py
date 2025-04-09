# Программирование на языке высокого уровня (Python).
# Задание week_05_1. Вариант 3
#
# Выполнил: Силина О.Р.
# Группа: ПИЖ-б-о-23-2(1)

import json
from typing import List
from complex_number import Complex

class ComplexCollection:
    def __init__(self, data: List[Complex] = None): #Инициализация коллекции комплексных чисел
        
        self._data = data if data is not None else []
    
    def __str__(self) -> str: #Строковое представление коллекции
        
        return "\n".join([f"[{i}] {str(num)}" for i, num in enumerate(self._data)])
    
    def __getitem__(self, index: int) -> Complex: #Доступ к элементам по индексу
        
        return self._data[index]
    
    def add(self, value: Complex) -> None: #Добавляет комплексное число в коллекцию
        
        self._data.append(value)
    
    def remove(self, index: int) -> None: #Удаляет комплексное число по индексу
        
        if 0 <= index < len(self._data):
            del self._data[index]
    
    def save(self, filename: str) -> None: #Сохраняет коллекцию в JSON-файл
       
        data = [num.to_dict() for num in self._data]
        with open(filename, 'w') as f:
            json.dump(data, f)
    
    def load(self, filename: str) -> None: #Загружает коллекцию из JSON-файла
        
        with open(filename, 'r') as f:
            data = json.load(f)
        self._data = [Complex.from_dict(item) for item in data]

# Пример использования
if __name__ == "__main__":
    # Создаем коллекцию
    collection = ComplexCollection()
    
    # Добавляем числа
    collection.add(Complex(1, 2))
    collection.add(Complex(-3, 4))
    collection.add(Complex(5, -6))
    
    # Выводим коллекцию
    print("Коллекция после добавления:")
    print(collection)
    
    # Удаляем элемент
    collection.remove(1)
    print("\nКоллекция после удаления элемента с индексом 1:")
    print(collection)
    
    # Сохраняем в файл
    collection.save("complex_numbers.json")
    
    # Загружаем из файла
    new_collection = ComplexCollection()
    new_collection.load("complex_numbers.json")
    print("\nКоллекция после загрузки из файла:")
    print(new_collection)