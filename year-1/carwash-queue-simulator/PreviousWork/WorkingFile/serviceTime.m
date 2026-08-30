function data = serviceTime(washBay)
    fprintf('\n%s:\n', washBay);
    num_rows = input('Enter the number of rows for service time: ');
    data = zeros(num_rows, 2);
    for i = 1:num_rows
        data(i, 1) = input('Enter service time: ');
        data(i, 2) = input('Enter probability: ');
    end
    displayServiceTime(data);
end
