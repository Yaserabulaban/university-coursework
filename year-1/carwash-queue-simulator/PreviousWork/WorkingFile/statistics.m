function statistics(cars)
    % Calculate and print simulation statistics
    numCars = cars.NumCars;
    serviceTime = cars.ServiceTime;
    interArrivalTime = cars.InterArrivalTime;
    
    arrivalTime = cumsum(interArrivalTime);
    totalServiceTime = sum(serviceTime);
    totalInterArrivalTime = sum(interArrivalTime);
    
    avgServiceTime = totalServiceTime / numCars;
    avgInterArrivalTime = totalInterArrivalTime / numCars;
    avgArrivalTime = mean(arrivalTime);
    avgTimeSpent = avgServiceTime + avgInterArrivalTime;
    
    fprintf('Average service time: %.2f minutes\n', avgServiceTime);
    fprintf('Average inter-arrival time: %.2f minutes\n', avgInterArrivalTime);
    fprintf('Average arrival time: %.2f minutes\n', avgArrivalTime);
    fprintf('Average time spent in system: %.2f minutes\n', avgTimeSpent);
end
