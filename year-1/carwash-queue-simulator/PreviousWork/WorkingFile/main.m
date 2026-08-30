fprintf('\n----------------------------------------\n');
fprintf('| Welcome To Car Wash Simulation |\n');
fprintf('----------------------------------------\n\n');

num_cars = input('Enter number of cars: ');

while true
    fprintf('Choose type of random number generator:\n');
    fprintf('1 - Linear Congruential Generator (LCG)\n');
    fprintf('2 - Random Variate Generator for Uniform Distribution\n');
    rng_type = input('Choice: ');
    if (rng_type == 1)
        fprintf('LCG: Xn = ((a*Xn-1)+c) mod m\n');
        seed = input('Enter seed value X0: ');
        randomServiceTime = LCG(num_cars, seed);
        randomInterArrivalTime = LCG(num_cars, seed);
        break;
    elseif (rng_type == 2)
        fprintf('Random Variate Generator for Uniform Distribution:\nXn = a+(b-a)*Rn\n');
        a = input('Enter a: ');
        b = input('Enter b: ');
        randomServiceTime = RVG(num_cars, a, b);
        randomInterArrivalTime = RVG(num_cars, a, b);
        break;
    else
        fprintf('Choose between 1 and 2 only\n');
    end
end

while true
    fprintf('Choose rule for waiting line:\n');
    fprintf('1 - Cars go to wash bays in sequential manner \n');
    fprintf('2 - Cars go to idle bay, and if all bays are idle, go to bay 1\n');
    lineRule = input('Choice: ');
    if (lineRule == 1 || lineRule == 2)
        break;
    else
        fprintf('Choose between 1 and 2 only\\n');
    end
end

serviceTime = [10,20,30,40,50,60,70,80,90,100;
               0.1,0.07,0.03,0.2,0.12,0.08,0.02,0.08,0.2,0.1;
               0.1,0.17,0.2,0.4,0.52,0.6,0.62,0.7,0.9,1.0;
               1,11,18,21,41,53,61,63,71,91;
               10,17,20,40,52,60,62,70,90,100];

interArrivalTime = [2,3,1,5,10,15,7,4,6,11;
                    0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1;
                    0.1,0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9,1.0;
                    1,11,21,31,41,51,61,71,81,91;
                    10,20,30,40,50,60,70,80,90,100];

% Initialize cars
cars = Car(randomInterArrivalTime, randomServiceTime, num_cars);

if (lineRule == 1)
    sequential(cars);
else
    IdleBay(cars);
end

% Print statistics
statistics(cars);

% Print detailed simulation table for each bay
printBays(cars);