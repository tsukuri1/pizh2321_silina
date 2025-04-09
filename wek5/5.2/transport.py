class TransportnoeSredstvo:
    """Базовый класс транспортного средства"""
    
    def __init__(self, name):
        self.name = name
        self._speed = 0
        self.__engine_status = False
    
    def start_engine(self):
        self.__engine_status = True
        print(f"{self.name}: Двигатель запущен")
    
    def stop_engine(self):
        self.__engine_status = False
        self._speed = 0
        print(f"{self.name}: Двигатель остановлен")
    
    def move(self, speed):
        if not self.__engine_status:
            print("Сначала запустите двигатель!")
            return
        self._speed = speed
        print(f"{self.name}: Движется со скоростью {speed} км/ч")

class VodnoeTS(TransportnoeSredstvo):
    """Водное транспортное средство"""
    
    def __init__(self, name):
        super().__init__(name)
        self.__anchor_down = True
    
    def raise_anchor(self):
        self.__anchor_down = False
        print("Якорь поднят")
    
    def move(self, speed):
        if self.__anchor_down:
            print("Нельзя плыть - якорь опущен!")
            return
        super().move(speed)

class KolesnoeTS(TransportnoeSredstvo):
    """Колесное транспортное средство"""
    
    def __init__(self, name):
        super().__init__(name)
        self._wheel_count = 4
    
    def move(self, speed):
        if speed > 120:
            print("Слишком высокая скорость для колесного ТС!")
            return
        super().move(speed)

class Avtomobil(KolesnoeTS):
    """Автомобиль"""
    
    def __init__(self, name):
        super().__init__(name)
        self.__fuel_level = 100
    
    def refuel(self, amount):
        self.__fuel_level = min(100, self.__fuel_level + amount)
        print(f"Заправлено. Топливо: {self.__fuel_level}%")
    
    def move(self, speed):
        if self.__fuel_level <= 0:
            print("Нет топлива!")
            return
        super().move(speed)
        self.__fuel_level -= 10