# Исследование

Исследование проделанной работы.

| Модель перцептрона   | 10 запусков | 100 запусков | 1000 запусков | Усредненное время работы 1 запуска |
| -------------------- | ----------- | ------------ | ------------- | ---------------------------------- |
| Матричный перцептрон | 264сек.     | 2650сек.     | 26320сек.     | 24сек.                             |
| -------------------- | ----------- | ------------ | ------------- | ---------------------------------- |
| Графовый перцептрон  | 520сек.     | 5150сек.     | 52570сек.     | 43сек.                             |
| -------------------- | ----------- | ------------ | ------------- | ---------------------------------- |


# Характеристики ПК

Huawei Matebook 13 AMD
Processor: AMD RyzenAMD Ryzen 7 3700U
RAM      : 16 GB

# Заключение

В нашей реализации матричный перцептрон отрабатывает быстрее графового. Тестовая выборка запускалась на 1 скрытом слое из 400 нейронов.