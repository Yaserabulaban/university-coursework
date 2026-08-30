BatterLife_data <- read.csv("BatteryLifeNew.csv")
mean_lifetime <- mean(battery_data$LifetimeHrs)
mean_lifetime <- mean(BatteryLife_data$LifetimeHrs)
mean_lifetime <- mean(BatterLife_data$LifetimeHrs)
sd_lifetime <- sd(BatterLife_data$LifetimeHrs)
View(BatterLife_data)
View(BatterLife_data)
View(BatterLife_data)
rm <- (ls)
rm <- (ls())
rm <- (BatterLife_data)
rm <- (ls(BatterLife_data)
s
rm() = ls()
rm(list = ls())
# Read data from .csv file
BatteryLife_data <- read.csv("BatteryLifeNew.csv")
# Define midpoints and frequencies
midpoints <- c(549, 562.5, 577.5, 592.5, 607.5, 622.5, 637.5, 652.5)
frequencies <- c(16, 54, 161, 274, 279, 138, 58, 20)
# Total number of batteries
total_freq <- sum(frequencies)
# Estimate the mean
mean_estimate <- sum(frequencies * midpoints) / total_freq
# Estimate variance
variance <- sum(frequencies * (midpoints - mean_estimate)^2) / (total_freq - 1)
# Estimate standard deviation
std_estimate <- sqrt(variance)
# Print results
mean_estimate
std_estimate
# data already loaded under the variable BatteryLife_data
# Calcualte mean and standard deviation
# Data already loaded in the varialbe BatteryLife_data
# Calculate mean and standard deviation
mean_lifetime <- mean(BatteryLife_data$LifetimeHrs)
std_lifetime <- sd(BatteryLife_data$LifetimeHrs)
# Printing output
mean_lifetime
std_lifetime
# Sample size and degrees of freedom
n <- length(BatteryLife_data$LifetimeHrs)
df <- n - 1
# t critical value
t_critical <- qt(0.975, df)
# Margin of error
margin_error <- t_critical * (std_lifetime / sqrt(n))
# Confidence interval
ci_lower <- mean_lifetime - margin_error
ci_upper <- mean_lifetime + margin_error
# Priting output
ci_lower
ci_upper
# Load the necessary libraries
library (ggplot2)
# Data already loaded in BatteryLife_data
# Plot the histogram with noraml curve
ggplot(BatteryLife_data, aes(x = LifetimeHrs)) +
geom_histogram(aes(y = ..density.. ), bins = 30, fill = "skyblue", color = "black")+
stat_function(fun = dnorm,
args = list(mean = mean(BatteryLife_data$LifetimeHrs), sd = sd(BatteryLife_data$LifetimeHrs)), color = "red", size = 1.2) +
labs(title = "Histogram of New Battery Lifetimes with Normal Curve Overlay", x = "Battery Lifetime (Hours)", y = "Density") + theme_minimal()
# ggplot2 library is already loaded + data is already loaded
# Q-Q plot
qqnorm(BatteryLife_data$LifetimeHrs, main = "Q-Q Plot of New Battery Lifetimes")
qqline(BatteryLife_data$LifetimeHrs, col = "red", lwd = 2)
# Shapiro-Wilk test
shapiro.test(BatteryLife_data$LifetimeHrs)
# Perform one-sample t-test
t_test_result <- t.test(BatteryLife_data$LifetimeHrs, mu=600)
# View t-statistic, degrees of freedom, and p-value
t_test_result$statistic
t_test_result$parameter
t_test_result$p.value
rm(list = ls())
# Load Data
sales_data <- read.csv("FreshFizz.csv")
sales_data$Date <- as.Date(sales_data$Date)
# Line plot of daily total sales
library(ggplot2)
ggplot(sales_data, aes(x = Date, y = Total_Sales)) +
geom_line(color = "blue" , size = 1) +
labs(title = "Daily Total Sales in 2024", x = "Date", y = "Total Sales (RM)") +
theme_minimal()
# Data already loaded
# Add period column
sales_data$Period <- ifelse(sales_data$Date < as.Date ("2024-06-01", "Before June", "After June"))
# Boxplot
ggplot(sales_Data, aes(x = Period, y = Total_sales, fill = Period)) +
geom_boxplot() +
labs(title = "Total Sales Before and After Mango Zing Launch", y = "Total Sales (RM)", x = "") + theme_minimal()
# Data already loaded
# Add period column
sales_data$Period <- ifelse(sales_data$Date < as.Date ("2024-06-01", "Before June", "After June"))
# Boxplot
ggplot(sales_data, aes(x = Period, y = Total_sales, fill = Period)) +
geom_boxplot() +
labs(title = "Total Sales Before and After Mango Zing Launch", y = "Total Sales (RM)", x = "") + theme_minimal()
ggplot(sales_data, aes(x = Period, y = Total_Sales, fill = Period)) +
geom_boxplot() +
labs(title = "Total Sales Before and After Mango Zing Launch", y = "Total Sales (RM)", x = "") + theme_minimal()
# Load data
sales_data <- read.csv("FreshFizz.csv")
sales_data$Date <- as.Date(sales_data$Date)
# Add period column
sales_data$Period <- ifelse(sales_data$Date < as.Date("2024-06-01"), "Before June", "After June")
# Boxplot
library(ggplot2)
ggplot(sales_data, aes(x = Period, y = Total_Sales, fill = Period)) +
geom_boxplot() +
labs(title = "Total Sales Before and After Mango Zing Launch", y = "Total Sales (RM)", x = "") +
theme_minimal()
# Summary statistics
tapply(sales_data$Total_Sales, sales_data$Period, mean)
tapply(sales_data$Total_Sales, sales_data$Period, sd)
# Data already loaded
# Perform ANOVA
anova_result <- aov(Total_Sales ~ Period, data = sales_data)
summary(anova_result)
# Filter post_launch data
post_launch <- subset(sales_data, Date >= as.Date("2024-06-01"))
# Perform ANOVA on the three original falvors
flavor_anova <- aov(values ~ variable, data = reshape2::melt(post_launch[,c("Cola_Classic","Lemon_Light", "Berry_Blast")]))
# Filter post-launch data
post_launch <- subset(sales_data, Date >= as.Date("2024-06-01"))
# Perform ANOVA on the three original flavors
flavor_anova <- aov(values ~ variable, data = reshape2::melt(post_launch[, c("Cola_Classic", "Lemon_Light", "Berry_Blast")]))
View(post_launch)
install.packages("reshape2")
library(reshape2)
# Filter post-launch data
post_launch <- subset(sales_data, Date >= as.Date("2024-06-01"))
# Perform ANOVA on the three original flavors
flavor_anova <- aov(values ~ variable, data = reshape2::melt(post_launch[, c("Cola_Classic", "Lemon_Light", "Berry_Blast")]))
# Filter data after Mango Zing launch
post_launch <- subset(sales_data, Date >= as.Date("2024-06-01"))
# Reshape the flavor data
flavor_data <- melt(post_launch[, c("Cola_Classic", "Lemon_Light", "Berry_Blast")])
# Run one-way ANOVA on flavor types
flavor_anova <- aov(value ~ variable, data = flavor_data)
summary(flavor_anova)
# Data already filtered
cor(post_launch$Mango_Zing, post_launch$Total_Sales, method = "pearson")
1. # Define midpoints and frequencies
2. midpoints <- c(549, 562.5, 577.5, 592.5, 607.5, 622.5, 637.5, 652.5)
