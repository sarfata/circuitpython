/*
 * This file is part of the MicroPython project, http://micropython.org/
 *
 * The MIT License (MIT)
 *
 * Copyright (c) 2019 Dan Halbert for Adafruit Industries
 * Copyright (c) 2018 Artur Pacholec
 * Copyright (c) 2017 Glenn Ruben Bakke
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include "py/objproperty.h"
#include "py/runtime.h"
#include "shared-bindings/bleio/Attribute.h"
#include "shared-bindings/bleio/Characteristic.h"
#include "shared-bindings/bleio/Descriptor.h"
#include "shared-bindings/bleio/UUID.h"

//| .. currentmodule:: bleio
//|
//| :class:`Characteristic` -- BLE service characteristic
//| =========================================================
//|
//| Stores information about a BLE service characteristic and allows reading
//| and writing of the characteristic's value.
//|
//| A Characteristic cannot be created directly. A new local Characteristic can be created
//| and attached to a Service by calling `Service.add_characteristic()`.
//| Remote Characteristic objects are created by `Central.discover_remote_services()`
//| or `Peripheral.discover_remote_services()` as part of remote Services.
//|

//|   .. attribute:: properties
//|
//|     An int bitmask representing which properties are set, specified as bitwise or'ing of
//|     of these possible values.
//|      `~Characteristic.BROADCAST`, `~Characteristic.INDICATE`, `~Characteristic.NOTIFY`,
//|      `~Characteristic.READ`, `~Characteristic.WRITE`, `~Characteristic.WRITE_NO_RESPONSE`.
//|
STATIC mp_obj_t bleio_characteristic_get_properties(mp_obj_t self_in) {
    bleio_characteristic_obj_t *self = MP_OBJ_TO_PTR(self_in);

    return MP_OBJ_NEW_SMALL_INT(common_hal_bleio_characteristic_get_properties(self));
}
STATIC MP_DEFINE_CONST_FUN_OBJ_1(bleio_characteristic_get_properties_obj, bleio_characteristic_get_properties);

const mp_obj_property_t bleio_characteristic_properties_obj = {
    .base.type = &mp_type_property,
    .proxy = { (mp_obj_t)&bleio_characteristic_get_properties_obj,
               (mp_obj_t)&mp_const_none_obj,
               (mp_obj_t)&mp_const_none_obj },
};

//|   .. attribute:: uuid
//|
//|     The UUID of this characteristic. (read-only)
//|       Will be ``None`` if the 128-bit UUID for this characteristic is not known.
//|
STATIC mp_obj_t bleio_characteristic_get_uuid(mp_obj_t self_in) {
    bleio_characteristic_obj_t *self = MP_OBJ_TO_PTR(self_in);

    bleio_uuid_obj_t *uuid = common_hal_bleio_characteristic_get_uuid(self);
    return uuid ? MP_OBJ_FROM_PTR(uuid) : mp_const_none;
}
STATIC MP_DEFINE_CONST_FUN_OBJ_1(bleio_characteristic_get_uuid_obj, bleio_characteristic_get_uuid);

const mp_obj_property_t bleio_characteristic_uuid_obj = {
    .base.type = &mp_type_property,
    .proxy = { (mp_obj_t)&bleio_characteristic_get_uuid_obj,
               (mp_obj_t)&mp_const_none_obj,
               (mp_obj_t)&mp_const_none_obj },
};

//|   .. attribute:: value
//|
//|     The value of this characteristic.
//|
STATIC mp_obj_t bleio_characteristic_get_value(mp_obj_t self_in) {
    bleio_characteristic_obj_t *self = MP_OBJ_TO_PTR(self_in);

    return common_hal_bleio_characteristic_get_value(self);
}
STATIC MP_DEFINE_CONST_FUN_OBJ_1(bleio_characteristic_get_value_obj, bleio_characteristic_get_value);

STATIC mp_obj_t bleio_characteristic_set_value(mp_obj_t self_in, mp_obj_t value_in) {
    bleio_characteristic_obj_t *self = MP_OBJ_TO_PTR(self_in);

    mp_buffer_info_t bufinfo;
    mp_get_buffer_raise(value_in, &bufinfo, MP_BUFFER_READ);

    common_hal_bleio_characteristic_set_value(self, &bufinfo);

    return mp_const_none;
}
STATIC MP_DEFINE_CONST_FUN_OBJ_2(bleio_characteristic_set_value_obj, bleio_characteristic_set_value);

const mp_obj_property_t bleio_characteristic_value_obj = {
    .base.type = &mp_type_property,
    .proxy = { (mp_obj_t)&bleio_characteristic_get_value_obj,
               (mp_obj_t)&bleio_characteristic_set_value_obj,
               (mp_obj_t)&mp_const_none_obj },
};

//|   .. attribute:: descriptors
//|
//|     A tuple of `bleio.Descriptor` that describe this characteristic. (read-only)
//|
STATIC mp_obj_t bleio_characteristic_get_descriptors(mp_obj_t self_in) {
    bleio_characteristic_obj_t *self = MP_OBJ_TO_PTR(self_in);
    // Return list as a tuple so user won't be able to change it.
    mp_obj_list_t *char_list = common_hal_bleio_characteristic_get_descriptor_list(self);
    return mp_obj_new_tuple(char_list->len, char_list->items);
}
STATIC MP_DEFINE_CONST_FUN_OBJ_1(bleio_characteristic_get_descriptors_obj, bleio_characteristic_get_descriptors);

const mp_obj_property_t bleio_characteristic_descriptors_obj = {
    .base.type = &mp_type_property,
    .proxy = { (mp_obj_t)&bleio_characteristic_get_descriptors_obj,
               (mp_obj_t)&mp_const_none_obj,
               (mp_obj_t)&mp_const_none_obj },
};

//|   .. attribute:: service (read-only)
//|
//|     The Service this Characteristic is a part of.
//|
STATIC mp_obj_t bleio_characteristic_get_service(mp_obj_t self_in) {
    bleio_characteristic_obj_t *self = MP_OBJ_TO_PTR(self_in);

    return common_hal_bleio_characteristic_get_service(self);
}
STATIC MP_DEFINE_CONST_FUN_OBJ_1(bleio_characteristic_get_service_obj, bleio_characteristic_get_service);

const mp_obj_property_t bleio_characteristic_service_obj = {
    .base.type = &mp_type_property,
    .proxy = { (mp_obj_t)&bleio_characteristic_get_service_obj,
               (mp_obj_t)&mp_const_none_obj,
               (mp_obj_t)&mp_const_none_obj },
};

//|   .. method:: add_descriptor(uuid, *, read_perm=`Attribute.OPEN`, write_perm=`Attribute.OPEN`, max_length=20, fixed_length=False, initial_value=b'')
//|
//|   Create a new `Descriptor` object, and add it to this Service.
//|
//|   :param bleio.UUID uuid: The uuid of the descriptor
//|   :param int read_perm: Specifies whether the descriptor can be read by a client, and if so, which
//|      security mode is required. Must be one of the integer values `Attribute.NO_ACCESS`, `Attribute.OPEN`,
//|      `Attribute.ENCRYPT_NO_MITM`, `Attribute.ENCRYPT_WITH_MITM`, `Attribute.LESC_ENCRYPT_WITH_MITM`,
//|      `Attribute.SIGNED_NO_MITM`, or `Attribute.SIGNED_WITH_MITM`.
//|   :param int write_perm: Specifies whether the descriptor can be written by a client, and if so, which
//|      security mode is required. Values allowed are the same as ``read_perm``.
//|   :param int max_length: Maximum length in bytes of the descriptor value. The maximum allowed is
//|      is 512, or possibly 510 if ``fixed_length`` is False. The default, 20, is the maximum
//|      number of data bytes that fit in a single BLE 4.x ATT packet.
//|   :param bool fixed_length: True if the descriptor value is of fixed length.
//|   :param buf initial_value: The initial value for this descriptor.
//|
//|   :return: the new `Descriptor`.
//|
STATIC mp_obj_t bleio_characteristic_add_descriptor(size_t n_args, const mp_obj_t *pos_args, mp_map_t *kw_args) {
    bleio_characteristic_obj_t *self = MP_OBJ_TO_PTR(pos_args[0]);

    enum { ARG_uuid, ARG_read_perm, ARG_write_perm,
           ARG_max_length, ARG_fixed_length, ARG_initial_value };
    static const mp_arg_t allowed_args[] = {
        { MP_QSTR_uuid,  MP_ARG_REQUIRED | MP_ARG_OBJ },
        { MP_QSTR_read_perm, MP_ARG_KW_ONLY| MP_ARG_INT, {.u_int = SECURITY_MODE_OPEN} },
        { MP_QSTR_write_perm, MP_ARG_KW_ONLY| MP_ARG_INT, {.u_int = SECURITY_MODE_OPEN} },
        { MP_QSTR_max_length, MP_ARG_KW_ONLY| MP_ARG_INT, {.u_int = 20} },
        { MP_QSTR_fixed_length, MP_ARG_KW_ONLY| MP_ARG_BOOL, {.u_bool = false} },
        { MP_QSTR_initial_value, MP_ARG_KW_ONLY| MP_ARG_OBJ, {.u_obj = mp_const_empty_bytes} },
    };

    mp_arg_val_t args[MP_ARRAY_SIZE(allowed_args)];
    mp_arg_parse_all(n_args - 1, pos_args + 1, kw_args, MP_ARRAY_SIZE(allowed_args), allowed_args, args);

    const mp_obj_t uuid_obj = args[ARG_uuid].u_obj;

    if (!MP_OBJ_IS_TYPE(uuid_obj, &bleio_uuid_type)) {
        mp_raise_ValueError(translate("Expected a UUID"));
    }
    bleio_uuid_obj_t *uuid = MP_OBJ_TO_PTR(uuid_obj);

    const bleio_attribute_security_mode_t read_perm = args[ARG_read_perm].u_int;
    common_hal_bleio_attribute_security_mode_check_valid(read_perm);

    const bleio_attribute_security_mode_t write_perm = args[ARG_write_perm].u_int;
    common_hal_bleio_attribute_security_mode_check_valid(write_perm);

    const mp_int_t max_length = args[ARG_max_length].u_int;
    const bool fixed_length =  args[ARG_fixed_length].u_bool;
    mp_obj_t initial_value = args[ARG_initial_value].u_obj;

    // Length will be validated in common_hal.
    mp_buffer_info_t initial_value_bufinfo;
    if (initial_value == mp_const_none) {
        if (fixed_length && max_length > 0) {
            initial_value = mp_obj_new_bytes_of_zeros(max_length);
        } else {
            initial_value = mp_const_empty_bytes;
        }
    }
    mp_get_buffer_raise(initial_value, &initial_value_bufinfo, MP_BUFFER_READ);

    bleio_descriptor_obj_t *descriptor = m_new_obj(bleio_descriptor_obj_t);
    descriptor->base.type = &bleio_descriptor_type;

    // Range checking on max_length arg is done by the common_hal layer, because
    // it may vary depending on underlying BLE implementation.
    common_hal_bleio_descriptor_construct(
        descriptor, uuid, read_perm, write_perm, max_length, fixed_length, &initial_value_bufinfo);

    common_hal_bleio_characteristic_add_descriptor(self, descriptor);

    return MP_OBJ_FROM_PTR(descriptor);
}
STATIC MP_DEFINE_CONST_FUN_OBJ_KW(bleio_characteristic_add_descriptor_obj, 2, bleio_characteristic_add_descriptor);

//|   .. method:: set_cccd(*, notify=False, indicate=False)
//|
//|     Set the remote characteristic's CCCD to enable or disable notification and indication.
//|
//|     :param bool notify: True if Characteristic should receive notifications of remote writes
//|     :param float indicate: True if Characteristic should receive indications of remote writes
//|
STATIC mp_obj_t bleio_characteristic_set_cccd(mp_uint_t n_args, const mp_obj_t *pos_args, mp_map_t *kw_args) {
    bleio_characteristic_obj_t *self = MP_OBJ_TO_PTR(pos_args[0]);

    enum { ARG_notify, ARG_indicate };
    static const mp_arg_t allowed_args[] = {
        { MP_QSTR_notify, MP_ARG_KW_ONLY | MP_ARG_BOOL, {.u_bool = false} },
        { MP_QSTR_indicate, MP_ARG_KW_ONLY | MP_ARG_BOOL, {.u_bool = false} },
    };

    mp_arg_val_t args[MP_ARRAY_SIZE(allowed_args)];
    mp_arg_parse_all(n_args - 1, pos_args + 1, kw_args, MP_ARRAY_SIZE(allowed_args), allowed_args, args);

    common_hal_bleio_characteristic_set_cccd(self, args[ARG_notify].u_bool, args[ARG_indicate].u_bool);

    return mp_const_none;
}
STATIC MP_DEFINE_CONST_FUN_OBJ_KW(bleio_characteristic_set_cccd_obj, 1, bleio_characteristic_set_cccd);


STATIC const mp_rom_map_elem_t bleio_characteristic_locals_dict_table[] = {
    { MP_ROM_QSTR(MP_QSTR_properties),     MP_ROM_PTR(&bleio_characteristic_get_properties) },
    { MP_ROM_QSTR(MP_QSTR_uuid),           MP_ROM_PTR(&bleio_characteristic_uuid_obj) },
    { MP_ROM_QSTR(MP_QSTR_value),          MP_ROM_PTR(&bleio_characteristic_value_obj) },
    { MP_ROM_QSTR(MP_QSTR_add_descriptor), MP_ROM_PTR(&bleio_characteristic_add_descriptor_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_cccd),       MP_ROM_PTR(&bleio_characteristic_set_cccd_obj) },

    // Bitmask constants to represent properties
//|   .. data:: BROADCAST
//|
//|      property: allowed in advertising packets
//|
//|   .. data:: INDICATE
//|
//|      property: server will indicate to the client when the value is set and wait for a response
//|
//|   .. data:: NOTIFY
//|
//|      property: server will notify the client when the value is set
//|
//|   .. data:: READ
//|
//|      property: clients may read this characteristic
//|
//|   .. data:: WRITE
//|
//|      property: clients may write this characteristic; a response will be sent back
//|
//|   .. data:: WRITE_NO_RESPONSE
//|
//|      property: clients may write this characteristic; no response will be sent back
//|
    { MP_ROM_QSTR(MP_QSTR_BROADCAST),         MP_ROM_INT(CHAR_PROP_BROADCAST) },
    { MP_ROM_QSTR(MP_QSTR_INDICATE),          MP_ROM_INT(CHAR_PROP_INDICATE) },
    { MP_ROM_QSTR(MP_QSTR_NOTIFY),            MP_ROM_INT(CHAR_PROP_NOTIFY) },
    { MP_ROM_QSTR(MP_QSTR_READ),              MP_ROM_INT(CHAR_PROP_READ) },
    { MP_ROM_QSTR(MP_QSTR_WRITE),             MP_ROM_INT(CHAR_PROP_WRITE) },
    { MP_ROM_QSTR(MP_QSTR_WRITE_NO_RESPONSE), MP_ROM_INT(CHAR_PROP_WRITE_NO_RESPONSE) },

};
STATIC MP_DEFINE_CONST_DICT(bleio_characteristic_locals_dict, bleio_characteristic_locals_dict_table);

STATIC void bleio_characteristic_print(const mp_print_t *print, mp_obj_t self_in, mp_print_kind_t kind) {
    bleio_characteristic_obj_t *self = MP_OBJ_TO_PTR(self_in);
    if (self->uuid) {
        mp_printf(print, "Characteristic(");
        bleio_uuid_print(print, MP_OBJ_FROM_PTR(self->uuid), kind);
        mp_printf(print, ")");
    } else {
        mp_printf(print, "<Characteristic with Unregistered UUID>");
    }
}

const mp_obj_type_t bleio_characteristic_type = {
    { &mp_type_type },
    .name = MP_QSTR_Characteristic,
    .print = bleio_characteristic_print,
    .locals_dict = (mp_obj_dict_t*)&bleio_characteristic_locals_dict,
};
