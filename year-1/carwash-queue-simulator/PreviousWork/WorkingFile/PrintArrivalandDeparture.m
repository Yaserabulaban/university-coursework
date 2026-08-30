function printArrivalandDeparture(car_id, arrival_time, start_time, end_time, bay)
    % Print arrival and departure messages for a car
    fprintf('Arrival of car %d at minute %.2f and queue at the bay %d\n', car_id, arrival_time, bay);
    fprintf('Service for car %d started at minute %.2f and ended at minute %.2f\n', car_id, start_time, end_time);
end
