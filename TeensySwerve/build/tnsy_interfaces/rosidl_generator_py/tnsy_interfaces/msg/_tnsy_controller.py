# generated from rosidl_generator_py/resource/_idl.py.em
# with input from tnsy_interfaces:msg/TnsyController.idl
# generated code does not contain a copyright notice


# Import statements for member types

import builtins  # noqa: E402, I100

import math  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_TnsyController(type):
    """Metaclass of message 'TnsyController'."""

    _CREATE_ROS_MESSAGE = None
    _CONVERT_FROM_PY = None
    _CONVERT_TO_PY = None
    _DESTROY_ROS_MESSAGE = None
    _TYPE_SUPPORT = None

    __constants = {
    }

    @classmethod
    def __import_type_support__(cls):
        try:
            from rosidl_generator_py import import_type_support
            module = import_type_support('tnsy_interfaces')
        except ImportError:
            import logging
            import traceback
            logger = logging.getLogger(
                'tnsy_interfaces.msg.TnsyController')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__msg__tnsy_controller
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__msg__tnsy_controller
            cls._CONVERT_TO_PY = module.convert_to_py_msg__msg__tnsy_controller
            cls._TYPE_SUPPORT = module.type_support_msg__msg__tnsy_controller
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__msg__tnsy_controller

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
            'TRANSLATION_MAGNITUDE__DEFAULT': 0.0,
            'TRANSLATION_ANGLE__DEFAULT': 0.0,
            'POINTING_MAGNITUDE__DEFAULT': 0.0,
            'POINTING_ANGLE__DEFAULT': 0.0,
            'ROTATION_SPEED__DEFAULT': 0.0,
            'ENABLE_SWITCH__DEFAULT': False,
        }

    @property
    def TRANSLATION_MAGNITUDE__DEFAULT(cls):
        """Return default value for message field 'translation_magnitude'."""
        return 0.0

    @property
    def TRANSLATION_ANGLE__DEFAULT(cls):
        """Return default value for message field 'translation_angle'."""
        return 0.0

    @property
    def POINTING_MAGNITUDE__DEFAULT(cls):
        """Return default value for message field 'pointing_magnitude'."""
        return 0.0

    @property
    def POINTING_ANGLE__DEFAULT(cls):
        """Return default value for message field 'pointing_angle'."""
        return 0.0

    @property
    def ROTATION_SPEED__DEFAULT(cls):
        """Return default value for message field 'rotation_speed'."""
        return 0.0

    @property
    def ENABLE_SWITCH__DEFAULT(cls):
        """Return default value for message field 'enable_switch'."""
        return False


class TnsyController(metaclass=Metaclass_TnsyController):
    """Message class 'TnsyController'."""

    __slots__ = [
        '_translation_magnitude',
        '_translation_angle',
        '_pointing_magnitude',
        '_pointing_angle',
        '_rotation_speed',
        '_enable_switch',
    ]

    _fields_and_field_types = {
        'translation_magnitude': 'float',
        'translation_angle': 'float',
        'pointing_magnitude': 'float',
        'pointing_angle': 'float',
        'rotation_speed': 'float',
        'enable_switch': 'boolean',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.translation_magnitude = kwargs.get(
            'translation_magnitude', TnsyController.TRANSLATION_MAGNITUDE__DEFAULT)
        self.translation_angle = kwargs.get(
            'translation_angle', TnsyController.TRANSLATION_ANGLE__DEFAULT)
        self.pointing_magnitude = kwargs.get(
            'pointing_magnitude', TnsyController.POINTING_MAGNITUDE__DEFAULT)
        self.pointing_angle = kwargs.get(
            'pointing_angle', TnsyController.POINTING_ANGLE__DEFAULT)
        self.rotation_speed = kwargs.get(
            'rotation_speed', TnsyController.ROTATION_SPEED__DEFAULT)
        self.enable_switch = kwargs.get(
            'enable_switch', TnsyController.ENABLE_SWITCH__DEFAULT)

    def __repr__(self):
        typename = self.__class__.__module__.split('.')
        typename.pop()
        typename.append(self.__class__.__name__)
        args = []
        for s, t in zip(self.__slots__, self.SLOT_TYPES):
            field = getattr(self, s)
            fieldstr = repr(field)
            # We use Python array type for fields that can be directly stored
            # in them, and "normal" sequences for everything else.  If it is
            # a type that we store in an array, strip off the 'array' portion.
            if (
                isinstance(t, rosidl_parser.definition.AbstractSequence) and
                isinstance(t.value_type, rosidl_parser.definition.BasicType) and
                t.value_type.typename in ['float', 'double', 'int8', 'uint8', 'int16', 'uint16', 'int32', 'uint32', 'int64', 'uint64']
            ):
                if len(field) == 0:
                    fieldstr = '[]'
                else:
                    assert fieldstr.startswith('array(')
                    prefix = "array('X', "
                    suffix = ')'
                    fieldstr = fieldstr[len(prefix):-len(suffix)]
            args.append(s[1:] + '=' + fieldstr)
        return '%s(%s)' % ('.'.join(typename), ', '.join(args))

    def __eq__(self, other):
        if not isinstance(other, self.__class__):
            return False
        if self.translation_magnitude != other.translation_magnitude:
            return False
        if self.translation_angle != other.translation_angle:
            return False
        if self.pointing_magnitude != other.pointing_magnitude:
            return False
        if self.pointing_angle != other.pointing_angle:
            return False
        if self.rotation_speed != other.rotation_speed:
            return False
        if self.enable_switch != other.enable_switch:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def translation_magnitude(self):
        """Message field 'translation_magnitude'."""
        return self._translation_magnitude

    @translation_magnitude.setter
    def translation_magnitude(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'translation_magnitude' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'translation_magnitude' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._translation_magnitude = value

    @builtins.property
    def translation_angle(self):
        """Message field 'translation_angle'."""
        return self._translation_angle

    @translation_angle.setter
    def translation_angle(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'translation_angle' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'translation_angle' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._translation_angle = value

    @builtins.property
    def pointing_magnitude(self):
        """Message field 'pointing_magnitude'."""
        return self._pointing_magnitude

    @pointing_magnitude.setter
    def pointing_magnitude(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'pointing_magnitude' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'pointing_magnitude' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._pointing_magnitude = value

    @builtins.property
    def pointing_angle(self):
        """Message field 'pointing_angle'."""
        return self._pointing_angle

    @pointing_angle.setter
    def pointing_angle(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'pointing_angle' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'pointing_angle' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._pointing_angle = value

    @builtins.property
    def rotation_speed(self):
        """Message field 'rotation_speed'."""
        return self._rotation_speed

    @rotation_speed.setter
    def rotation_speed(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'rotation_speed' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'rotation_speed' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._rotation_speed = value

    @builtins.property
    def enable_switch(self):
        """Message field 'enable_switch'."""
        return self._enable_switch

    @enable_switch.setter
    def enable_switch(self, value):
        if __debug__:
            assert \
                isinstance(value, bool), \
                "The 'enable_switch' field must be of type 'bool'"
        self._enable_switch = value
