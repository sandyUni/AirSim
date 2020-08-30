// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "UnrealSensorFactory.h"
#include "UnrealSensors/UnrealDistanceSensor.h"
#include "UnrealSensors/UnrealLidarSensor.h"
#include "UnrealSensors/UnrealUwbSensor.h"

UnrealSensorFactory::UnrealSensorFactory(AActor* actor, const NedTransform* ned_transform)
{
    setActor(actor, ned_transform);
}

std::unique_ptr<msr::airlib::SensorBase> UnrealSensorFactory::createSensorFromSettings(
    const AirSimSettings::SensorSetting* sensor_setting,const std::shared_ptr<SensorEnvBase> sensor_env  = std::shared_ptr<SensorEnvBase>(nullptr)) const
{
    using SensorBase = msr::airlib::SensorBase;

    switch (sensor_setting->sensor_type) {
    case SensorBase::SensorType::Distance:
        return std::unique_ptr<UnrealDistanceSensor>(new UnrealDistanceSensor(
            *static_cast<const AirSimSettings::DistanceSetting*>(sensor_setting), actor_, ned_transform_));
    case SensorBase::SensorType::Lidar:
        return std::unique_ptr<UnrealLidarSensor>(new UnrealLidarSensor(
            *static_cast<const AirSimSettings::LidarSetting*>(sensor_setting), actor_, ned_transform_));
    case SensorBase::SensorType::Uwb:
        return std::unique_ptr<UnrealUwbSensor>(new UnrealUwbSensor(
            *static_cast<const AirSimSettings::UwbSetting*>(sensor_setting), actor_, ned_transform_,sensor_env));
    default:
        return msr::airlib::SensorFactory::createSensorFromSettings(sensor_setting,sensor_env);
    }
}

void UnrealSensorFactory::setActor(AActor* actor, const NedTransform* ned_transform)
{
    actor_ = actor;
    ned_transform_ = ned_transform;
}