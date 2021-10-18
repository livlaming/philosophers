int main(int argc, char **argv)
{
    t_central central;
    t_philo philo;

    philo = NULL;
    central = malloc(sizeof(t_central));
    if (!central)
        return (-1);
    if ((argc != 5 && argc != 6) || check_input(argc, argv) == -1)
        return(error_message(central, philo, 1));
    
    return (0);
}