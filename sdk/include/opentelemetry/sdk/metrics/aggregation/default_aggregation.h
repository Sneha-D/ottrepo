// Copyright The OpenTelemetry Authors
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef ENABLE_METRICS_PREVIEW
#  include "opentelemetry/common/spin_lock_mutex.h"
#  include "opentelemetry/sdk/metrics/aggregation/aggregation.h"
#  include "opentelemetry/sdk/metrics/aggregation/drop_aggregation.h"
#  include "opentelemetry/sdk/metrics/aggregation/histogram_aggregation.h"
#  include "opentelemetry/sdk/metrics/aggregation/lastvalue_aggregation.h"
#  include "opentelemetry/sdk/metrics/aggregation/sum_aggregation.h"
#  include "opentelemetry/sdk/metrics/instruments.h"

#  include <mutex>

OPENTELEMETRY_BEGIN_NAMESPACE
namespace sdk
{
namespace metrics
{
class DefaultAggregation
{
public:
  static std::unique_ptr<Aggregation> CreateAggregation(
      const opentelemetry::sdk::metrics::InstrumentDescriptor &instrument_descriptor)
  {
    switch (instrument_descriptor.type_)
    {
      case InstrumentType::kCounter:
      case InstrumentType::kUpDownCounter:
      case InstrumentType::kObservableUpDownCounter:
        return (instrument_descriptor.value_type_ == InstrumentValueType::kLong)
                   ? std::move(std::unique_ptr<Aggregation>(new LongSumAggregation(true)))
                   : std::move(std::unique_ptr<Aggregation>(new DoubleSumAggregation(true)));
        break;
      case InstrumentType::kHistogram:
        return (instrument_descriptor.value_type_ == InstrumentValueType::kLong)
                   ? std::move(std::unique_ptr<Aggregation>(new LongHistogramAggregation()))
                   : std::move(std::unique_ptr<Aggregation>(new DoubleHistogramAggregation()));
        break;
      case InstrumentType::kObservableGauge:
        return (instrument_descriptor.value_type_ == InstrumentValueType::kLong)
                   ? std::move(std::unique_ptr<Aggregation>(new LongLastValueAggregation()))
                   : std::move(std::unique_ptr<Aggregation>(new DoubleLastValueAggregation()));
        break;
      default:
        return std::move(std::unique_ptr<Aggregation>(new DropAggregation()));
    };
  }
};

}  // namespace metrics
}  // namespace sdk
OPENTELEMETRY_END_NAMESPACE
#endif