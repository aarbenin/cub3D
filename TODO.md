# TODO List 🧌

## Текущие задачи

### 1. Масштабирование
- [ ] Проблема с искажением пропорций при изменении размеров окна.**
- [ ] Добавить функцию ресайзинга окна (сейчас изменения делаются вручную через изменение значений макросов) или отказаться от интерактивного ресайзинга и забить.
- **Примечание:** Это самая большая проблема на данном этапе 🚨.

### 2. Двери 🚪
- [ ] Проблемы с обработкой прозрачных пикселей в текстуре открытой двери (сейчас они отображаются как черные).
    - Возможные решения:
        1. Использовать отрисованную текстуру открытой двери (реализовано в текущей версии).
        2. Не использовать текстуру и убрать открытую дверь из проверки на столкновение (коридор появляется сразу после открытия двери, но выглядит это странно).
- [ ] Провести тестирование валидации карт, содержащих двери.
- [ ] Откалибровать взаимодействие с дверьми:
    - Определить оптимальное расстояние для открытия дверей (текущее расстояние кажется слишком большим).
    - Настроить площадь взаимодействия для открытия двери.

### 3. Миникарта
- [ ] Исправить незначительное отставание миниFOV от точки игрока при перемещении. Проблема не критична, но можно исправить, если останется время ⏳.

### 4. Оптимизация использования памяти
- [X] Проверить все аспекты использования памяти и исправить возможные утечки.

### 5. Norminette
- [ ] Раскидать функции по файлам и папкам (осмысленно) 📂.
- [ ] Исправить все ошибки.
- [ ] Перекреститься и забыть про Norminette 😅.

### 6. Исправить Makefile 🥸
- [ ] Убрать комменарии.
- [ ] Исправить проблему с fclean.