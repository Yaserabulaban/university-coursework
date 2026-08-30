function displayTable(car_WashBay)
    fprintf('%-10s%-15s%-15s\n', 'Car ID', 'Service Time', 'Arrival Time');
    for i = 1:size(car_WashBay, 1)
        fprintf('%-10d%-15d%-15d\n', car_WashBay(i, 1), car_WashBay(i, 2), car_WashBay(i, 3));
    end
end
