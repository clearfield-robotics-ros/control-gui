//
// control_gui.cpp
//
// Created: 27 Feb 2017
// Author: Adam Plowcha
//


#include <control_gui.h>
//#include <ui_control_gui.h>


namespace control_gui
{

ControlGUI::ControlGUI() :
    rqt_gui_cpp::Plugin(), widget_(0)
{
    setObjectName("ControlGUI");
}

ControlGUI::~ControlGUI()
{

}

void ControlGUI::initPlugin(qt_gui_cpp::PluginContext &context)
{
    std::string full_name_space = getNodeHandle().getNamespace();
    std::vector<std::string> components;
    boost::split(components, full_name_space, boost::is_any_of("/"));
    components.pop_back();
    std::string name_space = boost::algorithm::join(components, "/");

    /* Setup the widget */
    widget_ = new QWidget();
    ui_.setupUi(widget_);
    context.addWidget(widget_);

    // Status Reporting Boxes
    QObject::connect( this, SIGNAL(setStopGoText(const QString)),
                ui_.stop_go, SLOT(setText(const QString)));
    QObject::connect( this, SIGNAL(setStopGoColor(const QString)),
                ui_.stop_go, SLOT(setStyleSheet(const QString)));
    QObject::connect( this, SIGNAL(setActiveMd(const QString)),
                ui_.active_md, SLOT(setStyleSheet(const QString)));
    QObject::connect( this, SIGNAL(setIdleMd(const QString)),
                ui_.idle_md, SLOT(setStyleSheet(const QString)));
    QObject::connect( this, SIGNAL(setActivePr(const QString)),
                ui_.active_pr, SLOT(setStyleSheet(const QString)));
    QObject::connect( this, SIGNAL(setIdlePr(const QString)),
                ui_.idle_pr, SLOT(setStyleSheet(const QString)));
    QObject::connect( this, SIGNAL(setActiveMark(const QString)),
                ui_.active_mark, SLOT(setStyleSheet(const QString)));
    QObject::connect( this, SIGNAL(setIdleMark(const QString)),
                ui_.idle_mark, SLOT(setStyleSheet(const QString)));

    // State Transition Command Push Buttons
    QObject::connect(ui_.initializeButton, SIGNAL(clicked()),
                     this, SLOT(onInitButtonClicked()));
    QObject::connect(ui_.startButton, SIGNAL(clicked()),
                     this, SLOT(onStartButtonClicked()));
    QObject::connect(ui_.endButton, SIGNAL(clicked()),
                     this, SLOT(onEndButtonClicked()));

    current_state_sub = getNodeHandle().subscribe("/current_state", 1000, &ControlGUI::currentStateClbk, this);
//    report_sub = getNodeHandle().subscribe("/results", 1000, &ControlGUI::resultsClbk, this);
    desired_state_pub = getNodeHandle().advertise<std_msgs::Int16>("/desired_state",1000);

    // read parameters from launch file
//    getNodeHandle().getParam("/control_gui/control_gui/max_dist",max_dist);
//    getNodeHandle().getParam("/control_gui/control_gui/max_warning_delay",max_warning_delay);
//    getNodeHandle().getParam("/control_gui/control_gui/max_probe_time",max_probe_time);
//    getNodeHandle().getParam("/control_gui/control_gui/mine_threshold",mine_threshold);
//    getNodeHandle().getParam("/control_gui/control_gui/nonmine_threshold",nonmine_threshold);

}

void ControlGUI::shutdownPlugin()
{
    //Shutdown pubs and subs, etc
}

//All your remaining functions to go here...

QString blue = "background:rgb(0, 170, 255);";
QString red = "background-color: red;";
QString orange = "background-color: rgb(255, 107, 2);";
QString green = "background-color: green;";
QString transparent = "background:rgba(0,0,0,0);";

void ControlGUI::currentStateClbk(const std_msgs::Int16 &msg)
{
    switch(msg.data){
    case 0: // Idle
        emit setStopGoText("STOP");
        emit setStopGoColor(red);
        emit setActiveMd(transparent);
        emit setIdleMd(blue);
        emit setActivePr(transparent);
        emit setIdlePr(blue);
        emit setActiveMark(transparent);
        emit setIdleMark(blue);
//        ui_.startButton->setEnabled(true);
        break;
    case 1: // Calibrating
        emit setStopGoText("STOP");
        emit setStopGoColor(red);
        emit setActiveMd(orange);
        emit setIdleMd(transparent);
        emit setActivePr(orange);
        emit setIdlePr(transparent);
        emit setActiveMark(orange);
        emit setIdleMark(transparent);
//        ui_.endButton->setEnabled(false);
        ui_.startButton->setEnabled(true);
        break;
    case 2: // General Surveying
        emit setStopGoText("GO");
        emit setStopGoColor(green);
        emit setActiveMd(orange);
        emit setIdleMd(transparent);
        emit setActivePr(transparent);
        emit setIdlePr(blue);
        emit setActiveMark(transparent);
        emit setIdleMark(blue);
        ui_.startButton->setEnabled(false);
//        ui_.endButton->setEnabled(false);
        break;
    case 3: // MD Pinpointing
        emit setStopGoText("STOP");
        emit setStopGoColor(red);
        emit setActiveMd(orange);
        emit setIdleMd(transparent);
        emit setActivePr(transparent);
        emit setIdlePr(blue);
        emit setActiveMark(transparent);
        emit setIdleMark(blue);
        break;
    case 4: // Probing
        emit setStopGoText("STOP");
        emit setStopGoColor(red);
        emit setActiveMd(transparent);
        emit setIdleMd(blue);
        emit setActivePr(orange);
        emit setIdlePr(transparent);
        emit setActiveMark(transparent);
        emit setIdleMark(blue);
        break;
    case 5: // Marking
        emit setStopGoText("STOP");
        emit setStopGoColor(red);
        emit setActiveMd(transparent);
        emit setIdleMd(blue);
        emit setActivePr(transparent);
        emit setIdlePr(blue);
        emit setActiveMark(orange);
        emit setIdleMark(transparent);
        ui_.startButton->setEnabled(true);
        break;
    }
}

//void ControlGUI::resultsClbk(const control_gui::detection_result &msg)
//{
////    id.push_back(boost::lexical_cast<std::string>(msg.id));
////    truth.push_back(msg.truth);
////    radius_truth.push_back(boost::lexical_cast<std::string>(boost::format("%.2f") % msg.radius_truth));
////    x_truth.push_back(boost::lexical_cast<std::string>(boost::format("%.2f") % msg.x_truth));
////    y_truth.push_back(boost::lexical_cast<std::string>(boost::format("%.2f") % msg.y_truth));
////    estimate.push_back(msg.estimate);
////    radius_estimate.push_back(boost::lexical_cast<std::string>(boost::format("%.2f") % msg.radius_estimate));
////    x_estimate.push_back(boost::lexical_cast<std::string>(boost::format("%.2f") % msg.x_estimate));
////    y_estimate.push_back(boost::lexical_cast<std::string>(boost::format("%.2f") % msg.y_estimate));
////    estimate_euclidean_error.push_back(boost::lexical_cast<std::string>(boost::format("%.2f") % msg.estimate_euclidean_error));
////    warning_delay.push_back(boost::lexical_cast<std::string>(boost::format("%.2f") % msg.warning_delay));
////    probe_time.push_back(boost::lexical_cast<std::string>(boost::format("%.2f") % msg.probe_time));
//    id.push_back(msg.id);
//    truth.push_back(msg.truth);
//    radius_truth.push_back(msg.radius_truth);
//    x_truth.push_back(msg.x_truth);
//    y_truth.push_back(msg.y_truth);
//    estimate.push_back(msg.estimate);
//    radius_estimate.push_back(msg.radius_estimate);
//    x_estimate.push_back(msg.x_estimate);
//    y_estimate.push_back(msg.y_estimate);
//    estimate_euclidean_error.push_back(msg.estimate_euclidean_error);
//    warning_delay.push_back(msg.warning_delay);
//    probe_time.push_back(msg.probe_time);
//}

//std::vector<int> ControlGUI::mineCount()
//{
//    int count_mine_correct = 0;
//    int count_nonmine_correct = 0;
//    for (int i = 0; i<id.size(); i++){
//        if (truth.at(i)==estimate.at(i)){ // if the target was correctly identified
//            switch(truth.at(i)){
//            case 0: // nonmine correctly identified as a nonmine
//                count_nonmine_correct++;
//                break;
//            case 1: // mine correctly identified as a mine
//                count_mine_correct++;
//                break;
//            }
//        }
//    }
//    std::vector<int> mine_count;
//    mine_count.push_back(count_mine_correct);
//    mine_count.push_back(count_nonmine_correct);
//    return mine_count;
//}

//std::vector<bool> ControlGUI::verifyUnderLimit(const std::vector<float> &data, const float &limit)
//{
//    std::vector<bool> requirement_met;
//    for (int i = 0; i<data.size(); i++){
//        if (data.at(i)<=limit){
//            requirement_met.push_back(1);
//        }
//        else {
//            requirement_met.push_back(0);
//        }
//    }
//    return requirement_met;
//}

//void ControlGUI::formatOutput()
//{
////    std::string output; // std::string or QString
////    std::vector<bool> distance_met = verifyUnderLimit(estimate_euclidean_error, max_dist);
////    std::vector<bool> warning_delay_met = verifyUnderLimit(probe_time, max_probe_time);
////    std::vector<bool> probe_time_met = verifyUnderLimit(warning_delay, max_warning_delay);
////    for (int i = 0; i<id.size(); i++){
////        output = id.at(i) + radius_truth.at(i) + "\t" + x_truth.at(i);
////////        std::string truth = std::to_string(id.at(i));
//////    //        ROS_INFO(output);
////    }
////    QString qstr = QString::fromStdString(output);
////    emit setReportText(qstr);
//}

void ControlGUI::onInitButtonClicked()
{
    ui_.initializeButton->setEnabled(false);
    std_msgs::Int16 state;
    state.data = 1;
    desired_state_pub.publish(state);
}

void ControlGUI::onStartButtonClicked()
{
    ui_.startButton->setEnabled(false);
    std_msgs::Int16 state;
    state.data = 2;
    desired_state_pub.publish(state);
}

void ControlGUI::onEndButtonClicked()
{
//    ui_.endButton->setEnabled(false);
    std_msgs::Int16 state;
    state.data = 2;
    desired_state_pub.publish(state);
}

}

//This is a required line for Qt and ROS to work together
PLUGINLIB_EXPORT_CLASS(control_gui::ControlGUI, rqt_gui_cpp::Plugin)
