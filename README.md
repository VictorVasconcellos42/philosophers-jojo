# Philosophers
Se trata de um problema teórico proposto por Edsger Dijkstra em 1965 - The Dining Philosophers Problem - com foco em abordar problemas de concorrência e paralelismo, causados quando threads compartilham dos mesmos recursos.

<br></br>
<br></br>


O programa exibe no terminal uma mensagem para cada tarefa executada por cada um dos filósofos, acompanhada pelo milissegundo em que foi executada. Os filósofos são threads numeradas que seguem uma rotina de acordo com as regras do desafio. 

![[screenshot.png]]

## Desenvolvimento
A partir de um input no seguinte formato: (sendo o ultimo parâmetro opcional)

  ``` bash
  ./philo [num_philos] [time_to_eat] [time_to_die] [time_to_sleep] [meals_to_eat]
  ```

Threads são criadas de acordo com a quantidade de filósofos. e suas rotinas funcionam de acordo com os outros parâmetros passados.
Durante a resolução desse problema é necessário cumprir com uma serie de regras e inevitavelmente lidar com alguns fatores comuns:
- evitar starvation (dependendo dos valores passados, não é possível impedir)
- impedir deadlocks
- impedir data race, quando há race condition
- usar mutexes
- usar POSIX threads


## Como executar o projeto localmente
1. Cole esse comando no terminal para clonar e compilar:

  ``` bash
  git clone git@github.com:g-joana/philosophers.git && cd philosophers && make
  ```

2. Para executar digite o _binário_ + _parâmetros_. Exemplo:
  
  ``` bash
  ./philo 5 800 200 200
  ```
  _'./philo' + num_philos time_to_eat time_to_die time_to_sleep meals_to_eat_
