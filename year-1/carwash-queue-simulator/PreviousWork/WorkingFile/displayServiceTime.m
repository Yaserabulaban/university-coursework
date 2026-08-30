function displayServiceTime(data)
    fprintf('----------------------------------------------------\n');
    fprintf('| Service Time  |  Probability  |  CDF   | Range   |\n');
    fprintf('----------------------------------------------------\n');
    
    CDF = cumsum(data(:, 2));
    Last_Number = CDF * 100;
    First_Number = [1; cumsum(data(1:end - 1, 2)) * 100 + 1];
    
    for i = 1:size(data, 1)
        fprintf('|      %3d      |    %1.2f       |  %1.2f  |%3.0f-%3.0f  |\n', [data(i, 1), data(i, 2), CDF(i), First_Number(i), Last_Number(i)]);
    end
    
    fprintf('----------------------------------------------------\n');
end
