
rm(list=ls())
path = "D:\\Users\\mb624\\Documents\\GitHub\\VisionApplications\\perf-image-processing.csv"
data <- read.table(path, header=T, sep=";")

path2 =  "D:\\Users\\mb624\\Documents\\GitHub\\VisionApplications\\balanes-processing.csv"
data_balanes_rect <- read.table(path2, header=T, sep=";")

library(rgl)

summary(data)

data$app_type <- as.factor(data$app_type)
data$lang <- as.factor(data$lang)

summary(data)

boxplot(data$exe_time_ms)
plot(data$exe_time_ms)
abline(v = 900)
abline(h = 200)
abline(h = 80)

tools_java <- data$exe_time_ms[data$lang=="java" & data$app_type=="tools"]
tools_cpp <- data$exe_time_ms[data$lang=="c++" & data$app_type=="tools"][1:300]
balanes_java <- data$exe_time_ms[data$lang=="java" & data$app_type=="balanes"]
balanes_cpp <- data$exe_time_ms[data$lang=="c++" & data$app_type=="balanes"][1:300]
pois_java <- data$exe_time_ms[data$lang=="java" & data$app_type=="pois"]
pois_cpp <- data$exe_time_ms[data$lang=="c++" & data$app_type=="pois"][1:300]
balanes_rect_cpp <- data_balanes_rect$exe_time_ms

par(mfrow=c(4, 2))
plot(tools_java)
plot(tools_cpp)
plot(balanes_java)
plot(balanes_cpp)
plot(pois_java)
plot(pois_cpp)

par(mfrow=c(1, 2))
plot(balanes_java)
plot(balanes_rect_cpp)


tools_java = sort(tools_java)
tools_cpp = sort(tools_cpp)
balanes_java = sort(balanes_java)
balanes_cpp = sort(balanes_cpp)
pois_java = sort(pois_java)
pois_cpp = sort(pois_cpp)
balanes_rect_cpp <- sort(balanes_rect_cpp)

tools_java.mu <- mean(tools_java)
tools_cpp.mu <- mean(tools_cpp)
balanes_java.mu <- mean(balanes_java)
balanes_cpp.mu <- mean(balanes_cpp)
pois_java.mu <- mean(pois_java)
pois_cpp.mu <- mean(pois_cpp)
balanes_rect_cpp.mu <- mean(balanes_rect_cpp)

tools_ratio <- tools_java.mu / tools_cpp.mu
balanes_ratio <- balanes_java.mu / balanes_cpp.mu
pois_ratio <- pois_java.mu / pois_cpp.mu
balanes_rect_ratio <- balanes_java.mu / balanes_rect_cpp.mu

par(mfrow=c(4, 2))
plot(tools_java)
plot(tools_cpp)
plot(balanes_java)
plot(balanes_cpp)
plot(pois_java)
plot(pois_cpp)
plot(balanes_rect_cpp)


mean_set = data.frame(tools_java.mu, tools_cpp.mu,
                      balanes_java.mu, balanes_cpp.mu,
                      pois_java.mu, pois_cpp.mu,
                      balanes_rect_cpp.mu,
                      tools_ratio, balanes_ratio, pois_ratio, balanes_rect_ratio)
mean_set


t.test(tools_java, tools_cpp)
t.test(balanes_java, balanes_rect_cpp)
t.test(pois_java, pois_cpp)
