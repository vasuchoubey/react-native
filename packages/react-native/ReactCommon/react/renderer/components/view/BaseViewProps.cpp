/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include "BaseViewProps.h"

#include <algorithm>

#include <react/renderer/components/view/conversions.h>
#include <react/renderer/components/view/propsConversions.h>
#include <react/renderer/core/graphicsConversions.h>
#include <react/renderer/core/propsConversions.h>
#include <react/renderer/debug/debugStringConvertibleUtils.h>
#include <react/utils/CoreFeatures.h>

namespace facebook::react {

BaseViewProps::BaseViewProps(
    const PropsParserContext &context,
    BaseViewProps const &sourceProps,
    RawProps const &rawProps,
    bool shouldSetRawProps)
    : YogaStylableProps(context, sourceProps, rawProps, shouldSetRawProps),
      AccessibilityProps(context, sourceProps, rawProps),
      opacity(
          CoreFeatures::enablePropIteratorSetter ? sourceProps.opacity
                                                 : convertRawProp(
                                                       context,
                                                       rawProps,
                                                       "opacity",
                                                       sourceProps.opacity,
                                                       (Float)1.0)),
      backgroundColor(
          CoreFeatures::enablePropIteratorSetter
              ? sourceProps.backgroundColor
              : convertRawProp(
                    context,
                    rawProps,
                    "backgroundColor",
                    sourceProps.backgroundColor,
                    {})),
      borderRadii(
          CoreFeatures::enablePropIteratorSetter ? sourceProps.borderRadii
                                                 : convertRawProp(
                                                       context,
                                                       rawProps,
                                                       "border",
                                                       "Radius",
                                                       sourceProps.borderRadii,
                                                       {})),
      borderColors(
          CoreFeatures::enablePropIteratorSetter ? sourceProps.borderColors
                                                 : convertRawProp(
                                                       context,
                                                       rawProps,
                                                       "border",
                                                       "Color",
                                                       sourceProps.borderColors,
                                                       {})),
      borderCurves(
          CoreFeatures::enablePropIteratorSetter ? sourceProps.borderCurves
                                                 : convertRawProp(
                                                       context,
                                                       rawProps,
                                                       "border",
                                                       "Curve",
                                                       sourceProps.borderCurves,
                                                       {})),
      borderStyles(
          CoreFeatures::enablePropIteratorSetter ? sourceProps.borderStyles
                                                 : convertRawProp(
                                                       context,
                                                       rawProps,
                                                       "border",
                                                       "Style",
                                                       sourceProps.borderStyles,
                                                       {})),
      shadowColor(
          CoreFeatures::enablePropIteratorSetter ? sourceProps.shadowColor
                                                 : convertRawProp(
                                                       context,
                                                       rawProps,
                                                       "shadowColor",
                                                       sourceProps.shadowColor,
                                                       {})),
      shadowOffset(
          CoreFeatures::enablePropIteratorSetter ? sourceProps.shadowOffset
                                                 : convertRawProp(
                                                       context,
                                                       rawProps,
                                                       "shadowOffset",
                                                       sourceProps.shadowOffset,
                                                       {})),
      shadowOpacity(
          CoreFeatures::enablePropIteratorSetter
              ? sourceProps.shadowOpacity
              : convertRawProp(
                    context,
                    rawProps,
                    "shadowOpacity",
                    sourceProps.shadowOpacity,
                    {})),
      shadowRadius(
          CoreFeatures::enablePropIteratorSetter ? sourceProps.shadowRadius
                                                 : convertRawProp(
                                                       context,
                                                       rawProps,
                                                       "shadowRadius",
                                                       sourceProps.shadowRadius,
                                                       {})),
      transform(
          CoreFeatures::enablePropIteratorSetter ? sourceProps.transform
                                                 : convertRawProp(
                                                       context,
                                                       rawProps,
                                                       "transform",
                                                       sourceProps.transform,
                                                       {})),
      backfaceVisibility(
          CoreFeatures::enablePropIteratorSetter
              ? sourceProps.backfaceVisibility
              : convertRawProp(
                    context,
                    rawProps,
                    "backfaceVisibility",
                    sourceProps.backfaceVisibility,
                    {})),
      shouldRasterize(
          CoreFeatures::enablePropIteratorSetter
              ? sourceProps.shouldRasterize
              : convertRawProp(
                    context,
                    rawProps,
                    "shouldRasterize",
                    sourceProps.shouldRasterize,
                    {})),
      zIndex(
          CoreFeatures::enablePropIteratorSetter ? sourceProps.zIndex
                                                 : convertRawProp(
                                                       context,
                                                       rawProps,
                                                       "zIndex",
                                                       sourceProps.zIndex,
                                                       {})),
      pointerEvents(
          CoreFeatures::enablePropIteratorSetter
              ? sourceProps.pointerEvents
              : convertRawProp(
                    context,
                    rawProps,
                    "pointerEvents",
                    sourceProps.pointerEvents,
                    {})),
      hitSlop(
          CoreFeatures::enablePropIteratorSetter ? sourceProps.hitSlop
                                                 : convertRawProp(
                                                       context,
                                                       rawProps,
                                                       "hitSlop",
                                                       sourceProps.hitSlop,
                                                       {})),
      onLayout(
          CoreFeatures::enablePropIteratorSetter ? sourceProps.onLayout
                                                 : convertRawProp(
                                                       context,
                                                       rawProps,
                                                       "onLayout",
                                                       sourceProps.onLayout,
                                                       {})),
      events(
          CoreFeatures::enablePropIteratorSetter
              ? sourceProps.events
              : convertRawProp(context, rawProps, sourceProps.events, {})),
      collapsable(
          CoreFeatures::enablePropIteratorSetter ? sourceProps.collapsable
                                                 : convertRawProp(
                                                       context,
                                                       rawProps,
                                                       "collapsable",
                                                       sourceProps.collapsable,
                                                       true)),
      removeClippedSubviews(
          CoreFeatures::enablePropIteratorSetter
              ? sourceProps.removeClippedSubviews
              : convertRawProp(
                    context,
                    rawProps,
                    "removeClippedSubviews",
                    sourceProps.removeClippedSubviews,
                    false)),
      experimental_layoutConformance(
          CoreFeatures::enablePropIteratorSetter
              ? sourceProps.experimental_layoutConformance
              : convertRawProp(
                    context,
                    rawProps,
                    "experimental_layoutConformance",
                    sourceProps.experimental_layoutConformance,
                    {})) {}

#define VIEW_EVENT_CASE(eventType)                      \
  case CONSTEXPR_RAW_PROPS_KEY_HASH("on" #eventType): { \
    const auto offset = ViewEvents::Offset::eventType;  \
    ViewEvents defaultViewEvents{};                     \
    bool res = defaultViewEvents[offset];               \
    if (value.hasValue()) {                             \
      fromRawValue(context, value, res);                \
    }                                                   \
    events[offset] = res;                               \
    return;                                             \
  }

void BaseViewProps::setProp(
    const PropsParserContext &context,
    RawPropsPropNameHash hash,
    const char *propName,
    RawValue const &value) {
  // All Props structs setProp methods must always, unconditionally,
  // call all super::setProp methods, since multiple structs may
  // reuse the same values.
  YogaStylableProps::setProp(context, hash, propName, value);
  AccessibilityProps::setProp(context, hash, propName, value);

  static auto defaults = BaseViewProps{};

  switch (hash) {
    RAW_SET_PROP_SWITCH_CASE_BASIC(opacity);
    RAW_SET_PROP_SWITCH_CASE_BASIC(backgroundColor);
    RAW_SET_PROP_SWITCH_CASE_BASIC(shadowColor);
    RAW_SET_PROP_SWITCH_CASE_BASIC(shadowOffset);
    RAW_SET_PROP_SWITCH_CASE_BASIC(shadowOpacity);
    RAW_SET_PROP_SWITCH_CASE_BASIC(shadowRadius);
    RAW_SET_PROP_SWITCH_CASE_BASIC(transform);
    RAW_SET_PROP_SWITCH_CASE_BASIC(backfaceVisibility);
    RAW_SET_PROP_SWITCH_CASE_BASIC(shouldRasterize);
    RAW_SET_PROP_SWITCH_CASE_BASIC(zIndex);
    RAW_SET_PROP_SWITCH_CASE_BASIC(pointerEvents);
    RAW_SET_PROP_SWITCH_CASE_BASIC(hitSlop);
    RAW_SET_PROP_SWITCH_CASE_BASIC(onLayout);
    RAW_SET_PROP_SWITCH_CASE_BASIC(collapsable);
    RAW_SET_PROP_SWITCH_CASE_BASIC(removeClippedSubviews);
    RAW_SET_PROP_SWITCH_CASE_BASIC(experimental_layoutConformance);
    // events field
    VIEW_EVENT_CASE(PointerEnter);
    VIEW_EVENT_CASE(PointerEnterCapture);
    VIEW_EVENT_CASE(PointerMove);
    VIEW_EVENT_CASE(PointerMoveCapture);
    VIEW_EVENT_CASE(PointerLeave);
    VIEW_EVENT_CASE(PointerLeaveCapture);
    VIEW_EVENT_CASE(PointerOver);
    VIEW_EVENT_CASE(PointerOut);
    VIEW_EVENT_CASE(MoveShouldSetResponder);
    VIEW_EVENT_CASE(MoveShouldSetResponderCapture);
    VIEW_EVENT_CASE(StartShouldSetResponder);
    VIEW_EVENT_CASE(StartShouldSetResponderCapture);
    VIEW_EVENT_CASE(ResponderGrant);
    VIEW_EVENT_CASE(ResponderReject);
    VIEW_EVENT_CASE(ResponderStart);
    VIEW_EVENT_CASE(ResponderEnd);
    VIEW_EVENT_CASE(ResponderRelease);
    VIEW_EVENT_CASE(ResponderMove);
    VIEW_EVENT_CASE(ResponderTerminate);
    VIEW_EVENT_CASE(ResponderTerminationRequest);
    VIEW_EVENT_CASE(ShouldBlockNativeResponder);
    VIEW_EVENT_CASE(TouchStart);
    VIEW_EVENT_CASE(TouchMove);
    VIEW_EVENT_CASE(TouchEnd);
    VIEW_EVENT_CASE(TouchCancel);
    // BorderRadii
    SET_CASCADED_RECTANGLE_CORNERS(borderRadii, "border", "Radius", value);
    SET_CASCADED_RECTANGLE_EDGES(borderColors, "border", "Color", value);
    SET_CASCADED_RECTANGLE_EDGES(borderStyles, "border", "Style", value);
  }
}

#pragma mark - Convenience Methods

static BorderRadii ensureNoOverlap(BorderRadii const &radii, Size const &size) {
  // "Corner curves must not overlap: When the sum of any two adjacent border
  // radii exceeds the size of the border box, UAs must proportionally reduce
  // the used values of all border radii until none of them overlap."
  // Source: https://www.w3.org/TR/css-backgrounds-3/#corner-overlap

  auto insets = EdgeInsets{
      /* .left = */ radii.topLeft + radii.bottomLeft,
      /* .top = */ radii.topLeft + radii.topRight,
      /* .right = */ radii.topRight + radii.bottomRight,
      /* .bottom = */ radii.bottomLeft + radii.bottomRight,
  };

  auto insetsScale = EdgeInsets{
      /* .left = */
      insets.left > 0 ? std::min((Float)1.0, size.height / insets.left) : 0,
      /* .top = */
      insets.top > 0 ? std::min((Float)1.0, size.width / insets.top) : 0,
      /* .right = */
      insets.right > 0 ? std::min((Float)1.0, size.height / insets.right) : 0,
      /* .bottom = */
      insets.bottom > 0 ? std::min((Float)1.0, size.width / insets.bottom) : 0,
  };

  return BorderRadii{
      /* topLeft = */
      radii.topLeft * std::min(insetsScale.top, insetsScale.left),
      /* topRight = */
      radii.topRight * std::min(insetsScale.top, insetsScale.right),
      /* bottomLeft = */
      radii.bottomLeft * std::min(insetsScale.bottom, insetsScale.left),
      /* bottomRight = */
      radii.bottomRight * std::min(insetsScale.bottom, insetsScale.right),
  };
}

BorderMetrics BaseViewProps::resolveBorderMetrics(
    LayoutMetrics const &layoutMetrics) const {
  auto isRTL =
      bool{layoutMetrics.layoutDirection == LayoutDirection::RightToLeft};

  auto borderWidths = CascadedBorderWidths{
      /* .left = */ optionalFloatFromYogaValue(yogaStyle.border()[YGEdgeLeft]),
      /* .top = */ optionalFloatFromYogaValue(yogaStyle.border()[YGEdgeTop]),
      /* .right = */
      optionalFloatFromYogaValue(yogaStyle.border()[YGEdgeRight]),
      /* .bottom = */
      optionalFloatFromYogaValue(yogaStyle.border()[YGEdgeBottom]),
      /* .start = */
      optionalFloatFromYogaValue(yogaStyle.border()[YGEdgeStart]),
      /* .end = */ optionalFloatFromYogaValue(yogaStyle.border()[YGEdgeEnd]),
      /* .horizontal = */
      optionalFloatFromYogaValue(yogaStyle.border()[YGEdgeHorizontal]),
      /* .vertical = */
      optionalFloatFromYogaValue(yogaStyle.border()[YGEdgeVertical]),
      /* .all = */ optionalFloatFromYogaValue(yogaStyle.border()[YGEdgeAll]),
  };

  return {
      /* .borderColors = */ borderColors.resolve(isRTL, {}),
      /* .borderWidths = */ borderWidths.resolve(isRTL, 0),
      /* .borderRadii = */
      ensureNoOverlap(borderRadii.resolve(isRTL, 0), layoutMetrics.frame.size),
      /* .borderCurves = */ borderCurves.resolve(isRTL, BorderCurve::Circular),
      /* .borderStyles = */ borderStyles.resolve(isRTL, BorderStyle::Solid),
  };
}

bool BaseViewProps::getClipsContentToBounds() const {
  return yogaStyle.overflow() != YGOverflowVisible;
}

#pragma mark - DebugStringConvertible

#if RN_DEBUG_STRING_CONVERTIBLE
SharedDebugStringConvertibleList BaseViewProps::getDebugProps() const {
  const auto &defaultBaseViewProps = BaseViewProps();

  return AccessibilityProps::getDebugProps() +
      YogaStylableProps::getDebugProps() +
      SharedDebugStringConvertibleList{
          debugStringConvertibleItem(
              "opacity", opacity, defaultBaseViewProps.opacity),
          debugStringConvertibleItem(
              "backgroundColor",
              backgroundColor,
              defaultBaseViewProps.backgroundColor),
          debugStringConvertibleItem(
              "zIndex", zIndex, defaultBaseViewProps.zIndex.value_or(0)),
      };
}
#endif

} // namespace facebook::react
