
<a name="readme-top"></a>

<!-- PROJECT LOGO -->
<br />
<div align="center">
  <a href="https://github.com/osogostok/s21_STL_containers">
    <img src="./imgs/logo.png" alt="Logo" width="80" height="80">
  </a>

  <h3 align="center">STL Containers</h3>

  <p align="center">
    Реализация стадартной библиотеки шаблонов С++
    <br />
  </p>
</div>

<!-- TABLE OF CONTENTS -->
<details>
  <summary>Оглавление</summary>
  <ol>
    <li>
      <a href="#about-the-project">О проекте</a>
      <ul>
        <li><a href="#built-with">Зависимости</a></li>
      </ul>
    </li>
    <li>
      <a href="#getting-started">Устанвока</a>
    </li>
    <li><a href="#usage">Применение</a></li>
    <li><a href="#contributing">Вклад</a></li>
  </ol>
</details>



<!-- ABOUT THE PROJECT -->
## О проекте
Библиотека стандартных контейнеров, являющаяся универсальной коллекцией шаблонов классов и алгоритмов, позволяет программистам легко реализовывать общие структуры данных. 
Данная библиотека содержит следуюшие контейнеры:
* vector (вектор)
* list (список)
* stack (стек)  
* queue (очередь)
* map (словарь)
* set (множество)
* array (массив)
* multiset (мультимножество)

Контейнер управляет выделенной для его элементов памятью и предоставляет функции-элементы для доступа к ним, как непосредственно, так и через итераторы (объекты, имеющие свойства, аналогичные указателям).

Выбор наиболее подходящего контейнера для конкретного случая зависит не только от предоставляемой функциональности, но и от его эффективности при различных рабочих нагрузках.


Все контейнеры реализованы согласно стандартной библиотеки шаблонов <a href="https://en.cppreference.com/w/cpp/container">Containers library</a>.

<p align="right">(<a href="#readme-top">наверх</a>)</p>


## Зависимости
Проект написан на С++ стандарта C++17.

В качестве тестовой системы используются <a href="https://github.com/google/googletest/tree/main">GoogleTests</a>

<p align="right">(<a href="#readme-top">наверх</a>)</p>


<!-- GETTING STARTED -->
## Установка
Чтобы запустить локальную копию, выполните следующие простые шаги.

1. Клонирование репозитория 

```sh
git clone git@github.com:osogostok/s21_STL_containers.git
```
2. Переходим в проект для запуска тестов 

```sh
make test
```
<p align="right">(<a href="#readme-top">наверх</a>)</p>


<!-- CONTRIBUTING -->
## Вклад

Вклады — это то, что делает сообщество открытого исходного кода таким замечательным местом для обучения, вдохновения и творчества. Любой ваш вклад **очень ценится**.

Если у вас есть предложение, которое могло бы улучшить ситуацию, создайте форк репозитория и создайте запрос на включение. Также можно просто открыть задачу с тегом «улучшение».
Не забудьте поставить проекту звезду! Еще раз спасибо!

1. Форкните проект
2. Создайте свою ветку функций (`git checkout -b Feature/AmazingFeature`)
3. Зафиксируйте свои изменения (git commit -m 'Add some AmazingFeature'`)
4. Отправьте в ветку (`git push origin Feature/AmazingFeature`)
5. Откройте запрос на включение

<p align="right">(<a href="#readme-top">наверх</a>)</p>


