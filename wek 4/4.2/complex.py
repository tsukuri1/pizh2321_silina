import json

class Complex: # Класс для представления комплексных чисел вида a + bi, где a - действительная часть, b - мнимая часть
    
    def __init__(self, real=0, imaginary=0): # Инициализация комплексного числа
        self.real = real
        self.imaginary = imaginary
    
    @classmethod
    def from_string(cls, text):
        # Создает комплексное число из строки
        text = text.replace(" ", "")
        
        # Если нет 'i', значит это действительное число
        if "i" not in text:
            return cls(float(text), 0)
        
        # Обработка случаев с положительной мнимой частью (a+bi)
        if "+" in text:
            parts = text.split("+")
            real = float(parts[0])
            imag = float(parts[1].replace("i", ""))
        else:
            if "-" in text[1:]:
                parts = text.split("-", 1)
                real = float(parts[0])
                imag = -float(parts[1].replace("i", ""))
            else:
                # Случай когда только мнимая часть (bi)
                imag = float(text.replace("i", ""))
                real = 0
        
        return cls(real, imag)
    
    def __add__(self, other):
        # Сложение комплексных чисел: (a+c) + (b+d)i
        return Complex(self.real + other.real, 
                      self.imaginary + other.imaginary)
    
    def __sub__(self, other):
        # Вычитание комплексных чисел: (a-c) + (b-d)i
        return Complex(self.real - other.real,
                      self.imaginary - other.imaginary)
    
    def __mul__(self, other):
        # Умножение комплексных чисел по формуле: (a+bi)*(c+di) = (ac-bd) + (ad+bc)i
        return Complex(
            self.real*other.real - self.imaginary*other.imaginary,
            self.real*other.imaginary + self.imaginary*other.real
        )
    
    def __str__(self):
        # Строковое представление числа в формате a+bi
        return f"{self.real}{'+' if self.imaginary >= 0 else ''}{self.imaginary}i"
    
    def save(self, filename):
        # Сохраняет комплексное число в JSON-файл
        with open(filename, "w") as f:
            json.dump({"real": self.real, "imag": self.imaginary}, f)
    
    @classmethod
    def load(cls, filename):
        # Загружает комплексное число из JSON-файла
        with open(filename) as f:
            data = json.load(f)
        return cls(data["real"], data["imag"])